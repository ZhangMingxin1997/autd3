// File: constraint.hpp
// Project: holo
// Created Date: 13/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 12/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/emit_intensity.hpp"
#include "autd3/internal/native_methods.hpp"

namespace autd3::gain::holo {

/**
 * @brief Amplitude constraint
 */
class AmplitudeConstraint {
 public:
  /**
   * @brief Do nothing (this is equivalent to `Clamp(0, 1)`)
   */
  static AmplitudeConstraint dont_care() { return AmplitudeConstraint{internal::native_methods::AUTDGainHoloConstraintDotCare()}; }

  /**
   * @brief Normalize the value by dividing the maximum value
   */
  static AmplitudeConstraint normalize() { return AmplitudeConstraint{internal::native_methods::AUTDGainHoloConstraintNormalize()}; }

  /**
   * @brief Set all amplitudes to the specified value
   * @param value amplitude
   */
  static AmplitudeConstraint uniform(const double value) {
    return AmplitudeConstraint{internal::native_methods::AUTDGainHoloConstraintUniform(internal::EmitIntensity::new_normalized(value).pulse_width())};
  }

  /**
   * @brief Set all amplitudes to the specified value
   * @param value amplitude
   */
  static AmplitudeConstraint uniform(const uint16_t value) {
    return AmplitudeConstraint{
        internal::native_methods::AUTDGainHoloConstraintUniform(internal::EmitIntensity::new_pulse_width(value).pulse_width())};
  }

  /**
   * @brief Set all amplitudes to the specified value
   * @param value amplitude
   */
  static AmplitudeConstraint uniform(const internal::EmitIntensity value) {
    return AmplitudeConstraint{internal::native_methods::AUTDGainHoloConstraintUniform(value.pulse_width())};
  }

  /**
   * @brief Clamp all amplitudes to the specified range
   *
   * @param min_v minimum amplitude
   * @param max_v maximum amplitude
   */
  static AmplitudeConstraint clamp(const double min_v, const double max_v) {
    return AmplitudeConstraint{internal::native_methods::AUTDGainHoloConstraintClamp(min_v, max_v)};
  }

  [[nodiscard]] internal::native_methods::ConstraintPtr ptr() const { return _ptr; }

 private:
  explicit AmplitudeConstraint(const internal::native_methods::ConstraintPtr ptr) : _ptr(ptr) {}

  internal::native_methods::ConstraintPtr _ptr;
};

}  // namespace autd3::gain::holo
