// File: special.cpp
// Project: internal
// Created Date: 26/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 11/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#include <gtest/gtest.h>

#include <autd3/gain/uniform.hpp>
#include <autd3/internal/special.hpp>

#include "utils.hpp"

TEST(Internal, Stop) {
  auto autd = create_controller();

  ASSERT_TRUE(autd.send_async(autd3::gain::Uniform(1).with_phase(autd3::internal::pi)).get());
  for (auto& dev : autd.geometry()) {
    auto [duties, phases] = autd.link<autd3::link::Audit>().duties_and_phases(dev.idx(), 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 256; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 256; }));
  }

  ASSERT_TRUE(autd.send_async(autd3::internal::Stop()).get());
  for (auto& dev : autd.geometry()) {
    auto [duties, _] = autd.link<autd3::link::Audit>().duties_and_phases(dev.idx(), 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 0; }));
  }
}
