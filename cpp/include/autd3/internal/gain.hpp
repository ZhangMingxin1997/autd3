// File: gain.hpp
// Project: internal
// Created Date: 29/05/2023
// Author: Shun Suzuki
// -----
// Last Modified: 13/09/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/datagram.hpp"
#include "autd3/internal/native_methods.hpp"

namespace autd3::internal {

class Gain : public Datagram {
 public:
  Gain() = default;
  Gain(const Gain& obj) = default;
  Gain& operator=(const Gain& obj) = default;
  Gain(Gain&& obj) = default;
  Gain& operator=(Gain&& obj) = default;
  ~Gain() override = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry& geometry) const override { return AUTDGainIntoDatagram(gain_ptr(geometry)); }

  [[nodiscard]] virtual native_methods::GainPtr gain_ptr(const Geometry& geometry) const = 0;
};

#define AUTD3_IMPL_WITH_CACHE_GAIN(T)                           \
  [[nodiscard]] Cache<T> with_cache()& { return Cache(*this); } \
  [[nodiscard]] Cache<T>&& with_cache()&& { return Cache(std::move(*this)); }

#define AUTD3_IMPL_WITH_TRANSFORM_GAIN(T)                        \
  template <typename F>                                          \
  [[nodiscard]] Transform<T, F> with_transform(const F& f)& {    \
    return Transform(*this, f);                                  \
  }                                                              \
  template <typename F>                                          \
  [[nodiscard]] Transform<T, F>&& with_transform(const F& f)&& { \
    return Transform(std::move(*this), f);                       \
  }

}  // namespace autd3::internal
