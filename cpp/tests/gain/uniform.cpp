// File: uniform.cpp
// Project: gain
// Created Date: 26/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 06/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
// 

#include <autd3/gain/uniform.hpp>
#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Gain, Uniform) {
    auto autd = create_controller();

    ASSERT_TRUE(autd.send(autd3::gain::Uniform(0.5).with_phase(autd3::internal::pi)));

    for (auto& dev : autd.geometry()) {
        auto [duties, phases] = autd.link<autd3::link::Audit>().duties_and_phases(dev.idx(), 0);
        ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 85; }));
        ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 256; }));
    }
}
