// File: transform.hpp
// Project: modulation
// Created Date: 13/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 24/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/modulation.hpp"
#include "autd3/internal/native_methods.hpp"
#include "autd3/modulation/cache.hpp"
#include "autd3/modulation/radiation_pressure.hpp"

namespace autd3::modulation {

/**
 * @brief Modulation to transform the result of calculation
 */
template <class M, typename F>
class Transform final : public internal::Modulation, public IntoCache<Transform<M, F>>, public IntoRadiationPressure<Transform<M, F>> {
  using transform_f = uint8_t (*)(const void*, uint32_t, uint8_t);

 public:
  Transform(M m, const F& f) : _m(std::move(m)), _f(f) {
    _f_native = +[](const void* context, const uint32_t i, const uint8_t d) -> uint8_t {
      return static_cast<const Transform*>(context)->_f(static_cast<size_t>(i), autd3::internal::EmitIntensity(d)).value();
    };
  }

  [[nodiscard]] internal::native_methods::ModulationPtr modulation_ptr() const override {
    return internal::native_methods::AUTDModulationWithTransform(_m.modulation_ptr(), const_cast<void*>(reinterpret_cast<const void*>(_f_native)),
                                                                 const_cast<void*>(static_cast<const void*>(this)));
  }

 private:
  M _m;
  const F& _f;
  transform_f _f_native;
};

template <typename M>
class IntoTransform {
 public:
  template <typename F>
  [[nodiscard]] Transform<M, F> with_transform(const F& f) & {
    return Transform(*static_cast<M*>(this), f);
  }
  template <typename F>
  [[nodiscard]] Transform<M, F> with_transform(const F& f) && {
    return Transform(std::move(*static_cast<M*>(this)), f);
  }
};

}  // namespace autd3::modulation
