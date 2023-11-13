// File: null.cpp
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

#include <autd3/gain/null.hpp>

#include "utils.hpp"

TEST(Gain, Null) {
  auto autd = create_controller();

  ASSERT_TRUE(autd.send_async(autd3::gain::Null()).get());

  for (auto& dev : autd.geometry()) {
    auto [duties, phases] = autd.link().duties_and_phases(dev.idx(), 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 0; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 0; }));
  }
}
