// File: remote_soem.cpp
// Project: examples
// Created Date: 02/11/2022
// Author: Shun Suzuki
// -----
// Last Modified: 13/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
//

#include "autd3.hpp"
#include "autd3/link/soem.hpp"
#include "runner.hpp"
#include "util.hpp"

int main() try {
  auto autd = autd3::ControllerBuilder()
                  .add_device(autd3::AUTD3(autd3::Vector3::Zero(), autd3::Vector3::Zero()))
                  .open_with_async(autd3::link::RemoteSOEM::builder("127.0.0.1:8080"))
                  .get();

  return run(autd);
} catch (std::exception& e) {
  print_err(e);
  return -1;
}
