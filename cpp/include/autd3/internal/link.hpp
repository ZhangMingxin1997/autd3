// File: link.hpp
// Project: internal
// Created Date: 29/05/2023
// Author: Shun Suzuki
// -----
// Last Modified: 13/10/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/internal/native_methods.hpp"

namespace autd3::internal {

class LinkBuilder {
 public:
  virtual ~LinkBuilder() = default;
  LinkBuilder(const LinkBuilder& obj) = default;
  LinkBuilder& operator=(const LinkBuilder& obj) = default;
  LinkBuilder(LinkBuilder&& obj) = default;
  LinkBuilder& operator=(LinkBuilder&& obj) = default;
  LinkBuilder() = default;

  [[nodiscard]] virtual native_methods::LinkBuilderPtr ptr() const = 0;

  [[nodiscard]] virtual std::shared_ptr<void> props() const { return std::shared_ptr<void>(nullptr); }
};
}  // namespace autd3::internal
