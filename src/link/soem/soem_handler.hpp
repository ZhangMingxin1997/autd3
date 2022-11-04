// File: link_soem_impl.hpp
// Project: soem
// Created Date: 16/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 02/11/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 6285 6385 26437 26800 26498 26451 26495)
#endif
#if defined(__GNUC__) && !defined(__llvm__)
#pragma GCC diagnostic push
#endif
#ifdef __clang__
#pragma clang diagnostic push
#endif
#include <spdlog/fmt/fmt.h>
#if _MSC_VER
#pragma warning(pop)
#endif
#if defined(__GNUC__) && !defined(__llvm__)
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <atomic>
#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "autd3/driver/cpu/datagram.hpp"
#include "autd3/driver/cpu/ec_config.hpp"
#include "autd3/link/soem.hpp"
#include "ecat_thread.hpp"
#include "error_handler.hpp"

namespace autd3::link {

class SOEMHandler final {
 public:
  SOEMHandler(const bool high_precision, std::string ifname, const uint16_t sync0_cycle, const uint16_t send_cycle,
              std::function<void(std::string)> on_lost, const SYNC_MODE sync_mode, const std::chrono::milliseconds state_check_interval)
      : _high_precision(high_precision),
        _ifname(std::move(ifname)),
        _sync0_cycle(sync0_cycle),
        _send_cycle(send_cycle),
        _on_lost(std::move(on_lost)),
        _sync_mode(sync_mode),
        _is_open(false),
        _state_check_interval(state_check_interval) {}
  ~SOEMHandler() {
    try {
      close();
    } catch (std::exception&) {
    }
  }
  SOEMHandler(const SOEMHandler& v) noexcept = delete;
  SOEMHandler& operator=(const SOEMHandler& obj) = delete;
  SOEMHandler(SOEMHandler&& obj) = delete;
  SOEMHandler& operator=(SOEMHandler&& obj) = delete;

  static std::vector<EtherCATAdapter> enumerate_adapters() {
    auto* adapter = ec_find_adapters();
    std::vector<EtherCATAdapter> adapters;
    while (adapter != nullptr) {
      EtherCATAdapter info(std::string(adapter->desc), std::string(adapter->name));
      adapters.emplace_back(info);
      adapter = adapter->next;
    }
    return adapters;
  }

  size_t open(const int remaining) {
    if (is_open()) return 0;

    std::queue<driver::TxDatagram>().swap(_send_buf);

    const auto cycle_time = driver::EC_CYCLE_TIME_BASE_NANO_SEC * _send_cycle;
    spdlog::debug("send interval: {} [ns]", cycle_time);

    int wc = 0;
    if (_ifname.empty()) {
      spdlog::debug("looking for AUTD...");
      const auto* adapters = ec_find_adapters();
      bool found = false;
      for (const auto* adapter = adapters; adapter != nullptr; adapter = adapter->next) {
        _ifname = std::string(adapter->name);
        if (ec_init(_ifname.c_str()) <= 0) continue;
        wc = ec_config_init(0);
        if (wc <= 0) continue;
        found = true;
        for (auto i = 1; i <= wc; i++)
          if (std::strcmp(ec_slave[1].name, "AUTD") != 0) {
            found = false;
            break;
          }
        if (found) {
          spdlog::debug("AUTD found on {} ({})", adapter->name, adapter->desc);
          break;
        }
      }
      if (!found) {
        _is_open.store(false);
        if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
        throw std::runtime_error("No AUTD3 devices found");
      }
    } else {
      spdlog::debug("interface name: {}", _ifname);
      if (ec_init(_ifname.c_str()) <= 0) {
        _is_open.store(false);
        if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
        throw std::runtime_error(fmt::format("No socket connection on {}", _ifname));
      }
      wc = ec_config_init(0);
      if (wc <= 0) {
        _is_open.store(false);
        if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
        throw std::runtime_error("No slaves found");
      }
      for (auto i = 1; i <= wc; i++)
        if (std::strcmp(ec_slave[i].name, "AUTD") != 0) {
          _is_open.store(false);
          if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
          throw std::runtime_error(fmt::format("Slave[{}] is not AUTD3", i));
        }
    }
    spdlog::debug("Found {} devices", wc);

    _user_data = std::make_unique<uint32_t[]>(1);
    _user_data[0] = driver::EC_CYCLE_TIME_BASE_NANO_SEC * _sync0_cycle;
    ecx_context.userdata = _user_data.get();
    spdlog::debug("Sync0 interval: {} [ns]", driver::EC_CYCLE_TIME_BASE_NANO_SEC * _sync0_cycle);

    if (_sync_mode == SYNC_MODE::DC) {
      for (int cnt = 1; cnt <= ec_slavecount; cnt++)
        ec_slave[cnt].PO2SOconfigx = [](auto* context, auto slave) -> int {
          const auto cyc_time = static_cast<uint32_t*>(context->userdata)[0];
          ec_dcsync0(slave, true, cyc_time, 0U);
          return 0;
        };
      spdlog::debug("run mode: DC sync");
      spdlog::debug("Sync0 configured");
    }

    _io_map.resize(static_cast<size_t>(wc));
    ec_config_map(_io_map.get());

    ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);

    ec_configdc();

    ec_readstate();

    const auto expected_wkc = ec_group[0].outputsWKC * 2 + ec_group[0].inputsWKC;
    spdlog::debug("Calculated workcounter {}", expected_wkc);

    ec_slave[0].state = EC_STATE_OPERATIONAL;

    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);

    ec_writestate(0);

    _is_open.store(true);
    std::atomic<int32_t> wkc;
    _ecat_thread = std::thread([this, &wkc, cycle_time] {
      ecat_run(this->_high_precision, &this->_is_open, &wkc, cycle_time, this->_send_mtx, this->_send_buf, this->_io_map);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ec_statecheck(0, EC_STATE_OPERATIONAL, EC_TIMEOUTSTATE);

    if (ec_slave[0].state != EC_STATE_OPERATIONAL) {
      _is_open.store(false);
      if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
      if (remaining == 0) throw std::runtime_error("One ore more slaves are not responding: " + std::to_string(ec_slave[0].state));
      spdlog::debug("failed to reach op mode. retry opening...");
      return open(remaining - 1);
    }

    if (_sync_mode == SYNC_MODE::FREE_RUN) {
      for (int slave = 1; slave <= ec_slavecount; slave++)
        ec_dcsync0(static_cast<uint16_t>(slave), true, driver::EC_CYCLE_TIME_BASE_NANO_SEC * _sync0_cycle, 0U);
      spdlog::debug("run mode: Free Run");
      spdlog::debug("Sync0 configured");
    }

    _ecat_check_thread = std::thread([this, &wkc, expected_wkc] {
      while (this->_is_open.load()) {
        if ((wkc.load() < expected_wkc) || ec_group[0].docheckstate) error_handle(&this->_is_open, this->_on_lost);
        std::this_thread::sleep_for(_state_check_interval);
      }
    });

    return static_cast<size_t>(wc);
  }

  bool send(const driver::TxDatagram& tx) {
    if (!is_open()) throw std::runtime_error("link is closed");
    std::lock_guard lock(_send_mtx);
    _send_buf.push(tx.clone());
    return true;
  }

  bool receive(driver::RxDatagram& rx) const {
    if (!_is_open.load()) throw std::runtime_error("link is closed");
    rx.copy_from(_io_map.input());
    return true;
  }

  void close() {
    if (!is_open()) return;

    while (!_send_buf.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(1));

    _is_open.store(false);
    if (this->_ecat_thread.joinable()) this->_ecat_thread.join();
    if (this->_ecat_check_thread.joinable()) this->_ecat_check_thread.join();

    const auto cyc_time = static_cast<uint32_t*>(ecx_context.userdata)[0];
    for (uint16_t slave = 1; slave <= static_cast<uint16_t>(ec_slavecount); slave++) ec_dcsync0(slave, false, cyc_time, 0U);

    ec_slave[0].state = EC_STATE_SAFE_OP;
    ec_writestate(0);
    ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE);

    ec_slave[0].state = EC_STATE_PRE_OP;
    ec_writestate(0);
    ec_statecheck(0, EC_STATE_PRE_OP, EC_TIMEOUTSTATE);

    ec_close();
  }

  bool is_open() const { return _is_open.load(); }

 private:
  bool _high_precision;
  std::string _ifname;
  uint16_t _sync0_cycle;
  uint16_t _send_cycle;

  std::function<void(std::string)> _on_lost = nullptr;

  SYNC_MODE _sync_mode;

  IOMap _io_map;

  std::atomic<bool> _is_open;
  std::unique_ptr<uint32_t[]> _user_data;

  std::thread _ecat_thread;
  std::thread _ecat_check_thread;

  std::queue<driver::TxDatagram> _send_buf;
  std::mutex _send_mtx;

  std::chrono::milliseconds _state_check_interval;
};

}  // namespace autd3::link