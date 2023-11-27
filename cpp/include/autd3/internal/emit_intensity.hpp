// File: emit_intensity.hpp
// Project: internal
// Created Date: 12/11/2023
// Author: Shun Suzuki
// -----
// Last Modified: 25/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/native_methods.hpp"

namespace autd3::internal {
class EmitIntensity final {
 public:
  static EmitIntensity maximum() { return EmitIntensity{255}; }
  static EmitIntensity minimum() { return EmitIntensity{0}; }

  explicit EmitIntensity(const uint8_t value) : _value(value) {}

  [[nodiscard]] static EmitIntensity new_with_correction_alpha(const uint8_t value, const double alpha) {
    return EmitIntensity(native_methods::AUTDEmitIntensityNewWithCorrectionAlpha(value, alpha));
  }

  [[nodiscard]] static EmitIntensity new_with_correction(const uint8_t value) {
    return new_with_correction_alpha(value, native_methods::DEFAULT_CORRECTED_ALPHA);
  }

  [[nodiscard]] uint8_t value() const noexcept { return _value; }

 private:
  uint8_t _value;
};

}  // namespace autd3::internal