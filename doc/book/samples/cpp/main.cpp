#include <iostream>

#include "autd3.hpp"
#include "autd3/link/soem.hpp"

int main() try {
  autd3::Controller autd;

  autd.geometry().add_device(autd3::Vector3::Zero(), autd3::Vector3::Zero());

  auto link = autd3::link::SOEM().high_precision(true).build();
  autd.open(std::move(link));

  autd.check_trials = 50;

  autd.clear();

  autd.synchronize();

  const auto firm_infos = autd.firmware_infos();
  std::copy(firm_infos.begin(), firm_infos.end(), std::ostream_iterator<autd3::FirmwareInfo>(std::cout, "\n"));

  autd3::SilencerConfig config;
  autd.send(config);

  const auto focus = autd.geometry().center() + autd3::Vector3(0.0, 0.0, 150.0);
  autd3::gain::Focus g(focus);
  autd3::modulation::Sine m(150);

  autd.send(m, g);

  std::cout << "press enter to finish..." << std::endl;
  std::cin.ignore();

  autd.close();

  return 0;
} catch (std::exception& ex) {
  std::cerr << ex.what() << std::endl;
}