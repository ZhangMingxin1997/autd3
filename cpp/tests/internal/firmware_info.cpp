// File: firmware_info.cpp
// Project: internal
// Created Date: 26/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 09/10/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#include <gtest/gtest.h>

#include <autd3/internal/exception.hpp>
#include <autd3/internal/firmware_info.hpp>
#include <ranges>
#include <sstream>

#include "utils.hpp"

TEST(Internal, FirmwareInfo) {
  auto autd = create_controller();

  ASSERT_EQ("v3.0.2", autd3::internal::FirmwareInfo::latest_version());

  {
    const auto infos = autd.firmware_infos();
    std::ranges::for_each(std::ranges::views::iota(0) | std::ranges::views::take(infos.size()), [&](auto i) {
      std::stringstream ss;
      ss << i;
      ss << ": CPU = v3.0.2, FPGA = v3.0.2 [Emulator]";
      ASSERT_EQ(ss.str(), infos[i].info());
    });
  }

  {
    autd.link<autd3::link::Audit>().break_down();
    ASSERT_THROW((void)autd.firmware_infos(), autd3::internal::AUTDException);
  }
}