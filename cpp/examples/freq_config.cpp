// File: freq_config.cpp
// Project: examples
// Created Date: 31/08/2022
// Author: Shun Suzuki
// -----
// Last Modified: 03/06/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
//

#include "autd3.hpp"
#include "autd3/link/debug.hpp"
#include "util.hpp"

int main() try {
  // Here we use link::Debug for example, but you can use any other link.
  auto autd = autd3::Controller::builder()
                  .add_device(autd3::AUTD3(autd3::Vector3::Zero(), autd3::Vector3::Zero()))
                  .advanced_mode()
                  .open_with(autd3::link::Debug());

  std::for_each(autd.geometry().begin(), autd.geometry().end(), [](auto& tr) {
    tr.set_frequency(70e3);  // actual frequency is 163.84MHz/2341 ~ 69987 Hz
  });

  autd.send(autd3::Clear());
  autd.send(autd3::Synchronize());  // You must configure the frequencies of all transducers before synchronization.

  autd3::SilencerConfig silencer;
  autd.send(silencer);

  autd3::modulation::Sine m(150);
  const autd3::Vector3 center = autd.geometry().center() + autd3::Vector3(0.0, 0.0, 150.0);
  autd3::gain::Focus g(center);
  autd.send(m, g);

  std::cout << "press any key to finish..." << std::endl;
  std::cin.ignore();

  autd.close();

  return 0;
} catch (std::exception& e) {
  print_err(e);
  return -1;
}