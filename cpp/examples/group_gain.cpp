// File: group_gain.cpp
// Project: examples
// Created Date: 14/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 11/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#include "autd3.hpp"
#include "autd3/link/nop.hpp"
#include "runner.hpp"
#include "util.hpp"

int main() try {
  auto autd = autd3::Controller::builder()
                  .add_device(autd3::AUTD3(autd3::Vector3::Zero(), autd3::Vector3::Zero()))
                  .open_with_async(autd3::link::Nop::builder())
                  .get();

  const auto cx = autd.geometry().center().x();
  autd3::gain::Focus g1(autd.geometry().center() + autd3::Vector3(0, 0, 150));
  autd3::gain::Null g2;

  const auto g = autd3::gain::Group([&cx](const autd3::Device& dev, const autd3::Transducer& tr) -> std::optional<const char*> {
                   if (tr.position().x() < cx) return "focus";
                   return "null";
                 })
                     .set("focus", g1)
                     .set("null", g2);

  autd3::modulation::Sine m(150);
  autd.send_async(m, g).get();

  autd.close_async().get();

  return 0;

} catch (std::exception& e) {
  print_err(e);
  return -1;
}
