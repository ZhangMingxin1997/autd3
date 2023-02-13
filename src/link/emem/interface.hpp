// File: interface.hpp
// Project: emem
// Created Date: 06/02/2023
// Author: Shun Suzuki
// -----
// Last Modified: 13/02/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include <cstdint>

#include "result.hpp"

namespace autd3::link {

class Interface {
 public:
  virtual EmemResult send(const uint8_t* data, size_t size) = 0;
  virtual EmemResult read(uint8_t* data, size_t size) = 0;
  virtual void close() = 0;
  virtual ~Interface() = default;
  Interface() = default;
  Interface(const Interface& v) = default;
  Interface& operator=(const Interface& obj) = default;
  Interface(Interface&& obj) = default;
  Interface& operator=(Interface&& obj) = default;
};

}  // namespace autd3::link
