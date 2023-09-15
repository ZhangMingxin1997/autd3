// File: transform.hpp
// Project: modulation
// Created Date: 13/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 13/09/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/modulation.hpp"
#include "autd3/internal/native_methods.hpp"
#include "autd3/modulation/cache.hpp"

namespace autd3::modulation {

/**
 * @brief Modulation to cache the result of calculation
 */
class Transform final : public internal::Modulation {
 public:
  template <class M, typename F>
  Transform(M&& m, F& f) : _freq_div(m.sampling_frequency_division()) {
    static_assert(std::is_base_of_v<Modulation, std::remove_reference_t<M>>, "This is not Modulation");
    char err[256]{};
    const auto size = internal::native_methods::AUTDModulationSize(m.modulation_ptr(), err);
    if (size == internal::native_methods::AUTD3_ERR) throw internal::AUTDException(err);
    _buffer.resize(static_cast<size_t>(size));
    if (internal::native_methods::AUTDModulationCalc(m.modulation_ptr(), _buffer.data(), err) == internal::native_methods::AUTD3_ERR)
      throw internal::AUTDException(err);
    for (size_t i = 0; i < _buffer.size(); i++) _buffer[i] = f(i, _buffer[i]);
  }

  AUTD3_IMPL_WITH_CACHE_MODULATION

  [[nodiscard]] internal::native_methods::ModulationPtr modulation_ptr() const override {
    return internal::native_methods::AUTDModulationCustom(_freq_div, _buffer.data(), _buffer.size());
  }

 private:
  std::vector<double> _buffer;
  uint32_t _freq_div;
};

}  // namespace autd3::modulation