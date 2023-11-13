// File: remote_twincat.cpp
// Project: examples
// Created Date: 12/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 13/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
//

#include "autd3.hpp"
#include "autd3/link/twincat.hpp"
#include "runner.hpp"
#include "util.hpp"

int main() try {
  auto autd = autd3::ControllerBuilder()
                  .add_device(autd3::AUTD3(autd3::Vector3::Zero(), autd3::Vector3::Zero()))
                  .open_with_async(autd3::link::RemoteTwinCAT::builder("your TwinCATAUTDServer AMS net id (e.g. 172.16.99.2.1.1)"))
                  .get();

  return run(autd);
} catch (std::exception& e) {
  print_err(e);
  return -1;
}
