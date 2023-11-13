// File: transform.cpp
// Project: gain
// Created Date: 26/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 13/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#include <gtest/gtest.h>

#include <autd3/gain/uniform.hpp>

#include "utils.hpp"

TEST(Gain, Transform) {
  auto autd = create_controller();

  ASSERT_TRUE(autd.send_async(autd3::gain::Uniform(0.5)
                                  .with_phase(autd3::internal::pi)
                                  .with_transform([](const autd3::internal::Device& dev, const autd3::internal::Transducer&,
                                                     const autd3::internal::native_methods::Drive d) -> autd3::internal::native_methods::Drive {
                                    if (dev.idx() == 0) {
                                      return autd3::internal::native_methods::Drive{d.phase + autd3::internal::pi / 4, d.amp};
                                    }
                                    return autd3::internal::native_methods::Drive{d.phase - autd3::internal::pi / 4, d.amp};
                                  }))
                  .get());

  {
    auto [duties, phases] = autd.link().duties_and_phases(0, 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 85; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 256 + 64; }));
  }

  {
    auto [duties, phases] = autd.link().duties_and_phases(1, 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 85; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 256 - 64; }));
  }
}

TEST(Gain, TransformCheckOnlyForEnabled) {
  auto autd = create_controller();
  autd.geometry()[0].set_enable(false);

  std::vector cnt(autd.geometry().num_devices(), false);
  ASSERT_TRUE(autd.send_async(autd3::gain::Uniform(0.5)
                                  .with_phase(autd3::internal::pi)
                                  .with_transform([&cnt](const autd3::internal::Device& dev, const autd3::internal::Transducer&,
                                                         const autd3::internal::native_methods::Drive d) -> autd3::internal::native_methods::Drive {
                                    cnt[dev.idx()] = true;
                                    return d;
                                  }))
                  .get());

  ASSERT_FALSE(cnt[0]);
  ASSERT_TRUE(cnt[1]);

  {
    auto [duties, phases] = autd.link().duties_and_phases(0, 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 0; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 0; }));
  }
  {
    auto [duties, phases] = autd.link().duties_and_phases(1, 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 85; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 256; }));
  }
}
