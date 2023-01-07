// File: focus.hpp
// Project: stm
// Created Date: 11/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 07/01/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "autd3/core/stm/stm.hpp"
#include "autd3/driver/operation/focus_stm.hpp"

namespace autd3::core {

/**
 * @brief FocusSTM provides a function to display the focus sequentially and periodically.
 * @details FocusSTM uses a timer on the FPGA to ensure that the focus is precisely timed.
 * FocusSTM currently has the following three limitations.
 * 1. The maximum number of control points is 65536.
 * 2. Only a single focus can be displayed at a certain moment.
 */
struct FocusSTM final : STM {
  /**
   * @brief Control point and duty shift used in FocusSTM
   */
  struct Focus {
    /**
     * @brief Control point
     */
    Vector3 point;
    /**
     * @brief duty shift. The duty ratio will be (50% >> duty_shift).
     */
    uint8_t shift;

    explicit Focus(Vector3 point, const uint8_t shift = 0) : point(std::move(point)), shift(shift) {}
    ~Focus() = default;
    Focus(const Focus& v) noexcept = default;
    Focus& operator=(const Focus& obj) = default;
    Focus(Focus&& obj) = default;
    Focus& operator=(Focus&& obj) = default;
  };

  using value_type = Focus;

  FocusSTM() : STM() {}

  /**
   * @brief Set frequency of the STM
   * @param[in] freq Frequency of the STM
   * @details STM mode has some constraints, which determine the actual frequency of the STM.
   * @return driver::autd3_float_t Actual frequency of STM
   */
  driver::autd3_float_t set_frequency(const driver::autd3_float_t freq) override {
    const auto sample_freq = static_cast<driver::autd3_float_t>(size()) * freq;
    _op.freq_div = static_cast<uint32_t>(std::round(static_cast<driver::autd3_float_t>(driver::FPGA_CLK_FREQ) / sample_freq));
    return frequency();
  }

  /**
   * @brief Sampling frequency.
   */
  [[nodiscard]] driver::autd3_float_t sampling_frequency() const noexcept override {
    return static_cast<driver::autd3_float_t>(driver::FPGA_CLK_FREQ) / static_cast<driver::autd3_float_t>(_op.freq_div);
  }

  /**
   * @brief Sampling frequency division.
   */
  [[nodiscard]] uint32_t sampling_frequency_division() const noexcept override { return _op.freq_div; }

  /**
   * @brief Sampling frequency division.
   */
  uint32_t& sampling_frequency_division() noexcept override { return _op.freq_div; }

  std::optional<uint16_t>& start_idx() override { return _op.start_idx; }
  [[nodiscard]] std::optional<uint16_t> start_idx() const override { return _op.start_idx; }
  std::optional<uint16_t>& finish_idx() override { return _op.finish_idx; }
  [[nodiscard]] std::optional<uint16_t> finish_idx() const override { return _op.finish_idx; }

  /**
   * @brief Add control point
   * @param[in] point control point
   * @param[in] duty_shift duty shift. The duty ratio will be (50% >> duty_shift).
   */
  void add(const Vector3& point, uint8_t duty_shift = 0) { _points.emplace_back(point, duty_shift); }

  void push_back(const value_type& v) { _points.emplace_back(v); }

  [[nodiscard]] size_t size() const override { return _points.size(); }

  void init(const Mode, const Geometry& geometry) override {
    _op.init();
    _op.sound_speed = geometry.sound_speed;
    _op.device_map = geometry.device_map();
    _op.points.reserve(geometry.num_devices());
    size_t idx = 0;
    for (size_t i = 0; i < geometry.num_devices(); i++) {
      const Vector3 origin = geometry[idx].position();
      const Quaternion rotation = geometry[idx].rotation();
      const Eigen::Transform<driver::autd3_float_t, 3, Eigen::Affine> transform_matrix =
          Eigen::Translation<driver::autd3_float_t, 3>(origin) * rotation;
      const Eigen::Transform<driver::autd3_float_t, 3, Eigen::Affine> trans_inv = transform_matrix.inverse();

      std::vector<driver::STMFocus> local_points;
      local_points.reserve(_points.size());
      std::transform(_points.begin(), _points.end(), std::back_inserter(local_points), [&trans_inv](const auto& p) {
        const auto homo = Vector4(p.point[0], p.point[1], p.point[2], 1.0);
        const Vector4 local_position = trans_inv * homo;
        return driver::STMFocus(local_position.x(), local_position.y(), local_position.z(), p.shift);
      });
      _op.points.emplace_back(local_points);
      idx += geometry.device_map()[i];
    }
  }

  void pack(driver::TxDatagram& tx) override { _op.pack(tx); }

  [[nodiscard]] bool is_finished() const override { return _op.is_finished(); }

 private:
  std::vector<Focus> _points;
  driver::FocusSTM _op;
};

}  // namespace autd3::core
