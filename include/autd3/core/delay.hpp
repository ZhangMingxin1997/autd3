// File: delay.hpp
// Project: core
// Created Date: 01/06/2022
// Author: Shun Suzuki
// -----
// Last Modified: 15/11/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

#include "geometry.hpp"
#include "interface.hpp"

namespace autd3::core {

/**
 * @brief Gain controls the duty ratio and phase of each transducer in AUTD devices.
 */
struct ModDelayConfig final : DatagramBody {
  ModDelayConfig() : _sent(false) {}
  ~ModDelayConfig() override = default;
  ModDelayConfig(const ModDelayConfig& v) = default;
  ModDelayConfig& operator=(const ModDelayConfig& obj) = default;
  ModDelayConfig(ModDelayConfig&& obj) = default;
  ModDelayConfig& operator=(ModDelayConfig&& obj) = default;

  void init() override { _sent = false; }

  void pack(const Geometry& geometry, driver::TxDatagram& tx) override {
    geometry.driver()->null_body(tx);
    if (is_finished()) return;

    std::vector<uint16_t> delays;
    std::for_each(geometry.begin(), geometry.end(), [&](const auto& dev) {
      std::transform(dev.begin(), dev.end(), std::back_inserter(delays), [](const Transducer& tr) { return tr.mod_delay(); });
    });

    geometry.driver()->mod_delay(delays.data(), tx);

    _sent = true;
  }

  [[nodiscard]] bool is_finished() const noexcept override { return _sent; }

 private:
  bool _sent;
};

}  // namespace autd3::core
