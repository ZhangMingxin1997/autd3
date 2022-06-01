// File: controller.hpp
// Project: autd3
// Created Date: 10/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 01/06/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#include "autd3/driver/cpu/datagram.hpp"
#include "autd3/driver/cpu/ec_config.hpp"
#include "autd3/gain/primitive.hpp"
#include "core/geometry/dynamic_transducer.hpp"
#include "core/geometry/geometry.hpp"
#include "core/geometry/legacy_transducer.hpp"
#include "core/geometry/normal_phase_transducer.hpp"
#include "core/geometry/normal_transducer.hpp"
#include "core/interface.hpp"
#include "core/link.hpp"
#include "core/silencer_config.hpp"
#include "driver/firmware_version.hpp"

namespace autd3 {

/**
 * @brief AUTD Controller
 */
template <typename T, std::enable_if_t<std::is_base_of_v<core::Transducer<typename T::D>, T>, nullptr_t> = nullptr>
class ControllerX {
 public:
  ControllerX()
      : force_fan(false), reads_fpga_info(false), check_ack(false), _geometry(), _tx_buf(0), _rx_buf(0), _link(nullptr), _check_ack(false) {}

  /**
   * @brief Geometry of the devices
   */
  core::Geometry<T>& geometry() noexcept { return _geometry; }

  /**
   * @brief Geometry of the devices
   */
  [[nodiscard]] const core::Geometry<T>& geometry() const noexcept { return _geometry; }

  bool open(core::LinkPtr link) {
    _tx_buf = driver::TxDatagram(_geometry.num_devices());
    _rx_buf = driver::RxDatagram(_geometry.num_devices());

    _link = std::move(link);
    if (_link != nullptr) _link->open();
    return is_open();
  }

  /**
   * @brief Verify the device is properly connected
   */
  [[nodiscard]] bool is_open() const noexcept { return (_link != nullptr) && _link->is_open(); }

  /**
   * @brief Synchronize devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  bool synchronize() {
    push_ack();

    driver::force_fan(_tx_buf, force_fan);
    driver::reads_fpga_info(_tx_buf, reads_fpga_info);

    const auto msg_id = get_id();
    std::vector<uint16_t> cycles;
    std::for_each(_geometry.begin(), _geometry.end(), [&](const auto& dev) {
      std::transform(dev.begin(), dev.end(), std::back_inserter(cycles), [](const T& tr) { return tr.cycle(); });
    });

    sync(msg_id, _link->cycle_ticks(), cycles.data(), _tx_buf);

    if (!_link->send(_tx_buf)) {
      pop_ack();
      return false;
    }

    const auto success = wait_msg_processed(50);
    pop_ack();
    return success;
  }

  /**
   * @brief Update flags (force fan and reads_fpga_info)
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  bool update_flag() {
    core::NullHeader h;
    core::NullBody<T> b;
    return send(h, b);
  }

  /**
   * @brief FPGA info
   *  \return veetor of FPGAInfo. If failed, the vector is empty
   */
  std::vector<driver::FPGAInfo> read_fpga_info() {
    std::vector<driver::FPGAInfo> fpga_info;
    if (!_link->receive(_rx_buf)) return fpga_info;
    std::transform(_rx_buf.begin(), _rx_buf.end(), std::back_inserter(fpga_info),
                   [](const driver::RxMessage& rx) { return driver::FPGAInfo(rx.ack); });
    return fpga_info;
  }

  /**
   * @brief Clear all data in devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  bool clear() {
    push_ack();
    driver::clear(_tx_buf);
    if (!_link->send(_tx_buf)) {
      pop_ack();
      return false;
    }
    const auto success = wait_msg_processed(200);
    pop_ack();
    return success;
  }

  /**
   * @brief Stop outputting
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  bool stop();

  /**
   * @brief Close the controller
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  bool close() {
    if (!stop()) return false;
    if (!clear()) return false;
    _link->close();
    return true;
  }

  /**
   * @brief Enumerate firmware information
   * \return vector of driver::FirmwareInfo. If failed, the vector is empty.
   */
  [[nodiscard]] std::vector<driver::FirmwareInfo> firmware_infos() {
    std::vector<driver::FirmwareInfo> firmware_infos;

    push_ack();

    const auto pack_ack = [&]() -> std::vector<uint8_t> {
      std::vector<uint8_t> acks;
      if (!_link->send(_tx_buf)) return acks;
      if (!wait_msg_processed(50)) return acks;
      std::transform(_rx_buf.begin(), _rx_buf.end(), std::back_inserter(acks), [](driver::RxMessage msg) noexcept { return msg.ack; });
      return acks;
    };

    cpu_version(_tx_buf);
    const auto cpu_versions = pack_ack();
    if (cpu_versions.empty()) {
      pop_ack();
      return firmware_infos;
    }

    fpga_version(_tx_buf);
    const auto fpga_versions = pack_ack();
    if (fpga_versions.empty()) {
      pop_ack();
      return firmware_infos;
    }

    fpga_functions(_tx_buf);
    const auto fpga_functions = pack_ack();
    if (fpga_functions.empty()) {
      pop_ack();
      return firmware_infos;
    }

    pop_ack();

    for (size_t i = 0; i < _geometry.num_devices(); i++)
      firmware_infos.emplace_back(i, cpu_versions.at(i), fpga_versions.at(i), fpga_functions.at(i));

    return firmware_infos;
  }

  /**
   * @brief Send header data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename H>
  auto send(H& header) -> typename std::enable_if_t<std::is_base_of_v<core::DatagramHeader, H>, bool> {
    core::NullBody<T> b;
    return send(header, b);
  }

  /**
   * @brief Send header data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename H>
  auto send(H&& header) -> typename std::enable_if_t<std::is_base_of_v<core::DatagramHeader, H>, bool> {
    return send(header);
  }

  /**
   * @brief Send body data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename B>
  auto send(B& body) -> typename std::enable_if_t<std::is_base_of_v<core::DatagramBody<T>, B>, bool> {
    core::NullHeader h;
    return send(h, body);
  }

  /**
   * @brief Send body data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename B>
  auto send(B&& body) -> typename std::enable_if_t<std::is_base_of_v<core::DatagramBody<T>, B>, bool> {
    return send(body);
  }

  /**
   * @brief Send header and body data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename H, typename B>
  auto send(H& header, B& body) ->
      typename std::enable_if_t<std::is_base_of_v<core::DatagramHeader, H> && std::is_base_of_v<core::DatagramBody<T>, B>, bool> {
    header.init();
    body.init();

    driver::force_fan(_tx_buf, force_fan);
    driver::reads_fpga_info(_tx_buf, reads_fpga_info);

    while (true) {
      const auto msg_id = get_id();
      header.pack(msg_id, _tx_buf);
      body.pack(_geometry, _tx_buf);
      _link->send(_tx_buf);
      if (!wait_msg_processed(50)) return false;
      if (header.is_finished() && body.is_finished()) break;
      if (!check_ack) std::this_thread::sleep_for(std::chrono::microseconds(driver::EC_SYNC0_CYCLE_TIME_MICRO_SEC * _link->cycle_ticks()));
    }
    return true;
  }

  /**
   * @brief Send header and body data to devices
   * \return if this function returns true and check_ack is true, it guarantees that the devices have processed the data.
   */
  template <typename H, typename B>
  auto send(H&& header, B&& body) ->
      typename std::enable_if_t<std::is_base_of_v<core::DatagramHeader, H> && std::is_base_of_v<core::DatagramBody<T>, B>, bool> {
    return send(header, body);
  }

  /**
   * @brief If true, the fan will be forced to start.
   */
  bool force_fan;

  /**
   * @brief If true, the devices return FPGA info in all frames. The FPGA info can be read by fpga_info().
   */
  bool reads_fpga_info;

  /**
   * @brief If true, this controller check ack from devices.
   */
  bool check_ack;

 private:
  static uint8_t get_id() noexcept {
    static std::atomic id_body{driver::MSG_BEGIN};
    if (uint8_t expected = driver::MSG_END; !id_body.compare_exchange_weak(expected, driver::MSG_BEGIN)) id_body.fetch_add(0x01);
    return id_body.load();
  }

  bool wait_msg_processed(const size_t max_trial) {
    if (!check_ack) return true;

    const auto msg_id = _tx_buf.header().msg_id;
    for (size_t i = 0; i < max_trial; i++) {
      if (!_link->receive(_rx_buf)) continue;
      if (_rx_buf.is_msg_processed(msg_id)) return true;
      std::this_thread::sleep_for(std::chrono::microseconds(driver::EC_SYNC0_CYCLE_TIME_MICRO_SEC * _link->cycle_ticks()));
    }
    return false;
  }

  void push_ack() {
    _check_ack = check_ack;
    check_ack = true;
  }

  void pop_ack() { check_ack = _check_ack; }

  core::Geometry<T> _geometry;
  driver::TxDatagram _tx_buf;
  driver::RxDatagram _rx_buf;
  core::LinkPtr _link;

  bool _check_ack;
};

template <>
bool ControllerX<autd3::core::LegacyTransducer>::stop() {
  SilencerConfig config;
  gain::Null<autd3::core::LegacyTransducer> g;
  return send(config, g);
}

template <>
bool ControllerX<autd3::core::NormalTransducer>::stop() {
  SilencerConfig config;
  gain::Null<autd3::core::NormalTransducer> g;
  return send(config, g);
}

template <>
bool ControllerX<autd3::core::NormalPhaseTransducer>::stop() {
  SilencerConfig config;
  autd3::core::Amplitudes<autd3::core::NormalPhaseTransducer> g(_geometry, 0.0);
  return send(config, g);
}

template <>
bool ControllerX<autd3::core::DynamicTransducer>::stop() {
  SilencerConfig config;
  switch (autd3::core::DynamicTransducer::mode()) {
    case core::TransducerMode::NormalPhase:
      return send(config, autd3::core::Amplitudes<autd3::core::DynamicTransducer>(_geometry, 0.0));
    default:
      return send(config, gain::Null<autd3::core::DynamicTransducer>());
  }
}

/**
 * @brief AUTD Controller with legacy (40kHz) transducer
 */
using Controller = ControllerX<core::LegacyTransducer>;

}  // namespace autd3
