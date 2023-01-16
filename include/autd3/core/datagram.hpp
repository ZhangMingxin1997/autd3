// File: datagram.hpp
// Project: core
// Created Date: 11/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 16/01/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include "autd3/core/geometry.hpp"
#include "autd3/driver/operation/null.hpp"

namespace autd3::core {

struct DatagramHeader;
struct DatagramBody;

/**
 * @brief Pack of DatagramHeader and DatagramBody
 *
 * @tparam H DatagramHeader
 * @tparam B DatagramBody
 */
template <typename H, typename B>
struct DatagramPack {
  H header;
  B body;
};

/**
 * @brief Pack of DatagramHeader and DatagramBody references
 */
struct DatagramPackRef {
  DatagramHeader& header;
  DatagramBody& body;
};

template <typename H, typename B>
auto operator,(H&& h, B&& b) -> std::enable_if_t<std::is_base_of_v<DatagramHeader, H> && std::is_base_of_v<DatagramBody, B> &&
                                                     !std::is_lvalue_reference_v<H> && !std::is_lvalue_reference_v<B>,
                                                 DatagramPack<H, B>> {
  return {std::move(h), std::move(b)};
}

template <typename H, typename B>
auto operator,(H&& h, B&& b) -> std::enable_if_t<std::is_base_of_v<DatagramHeader, std::remove_reference_t<H>> &&
                                                     std::is_base_of_v<DatagramBody, std::remove_reference_t<B>> && std::is_lvalue_reference_v<H> &&
                                                     std::is_lvalue_reference_v<B>,
                                                 DatagramPackRef> {
  return {h, b};
}

template <typename H, typename B>
auto operator,(B&& b, H&& h) -> std::enable_if_t<std::is_base_of_v<DatagramHeader, H> && std::is_base_of_v<DatagramBody, B> &&
                                                     !std::is_lvalue_reference_v<H> && !std::is_lvalue_reference_v<B>,
                                                 DatagramPack<H, B>> {
  return {std::move(h), std::move(b)};
}

template <typename H, typename B>
auto operator,(B&& b, H&& h) -> std::enable_if_t<std::is_base_of_v<DatagramHeader, std::remove_reference_t<H>> &&
                                                     std::is_base_of_v<DatagramBody, std::remove_reference_t<B>> && std::is_lvalue_reference_v<H> &&
                                                     std::is_lvalue_reference_v<B>,
                                                 DatagramPackRef> {
  return {h, b};
}

/**
 * @brief DatagramHeader is a data to be packed in the Header part of the driver::TxDatagram
 */
struct DatagramHeader {
  DatagramHeader() = default;
  virtual ~DatagramHeader() = default;
  DatagramHeader(const DatagramHeader& v) = default;
  DatagramHeader& operator=(const DatagramHeader& obj) = default;
  DatagramHeader(DatagramHeader&& obj) = default;
  DatagramHeader& operator=(DatagramHeader&& obj) = default;

  virtual std::unique_ptr<driver::Operation> operation() = 0;
};

/**
 * @brief DatagramBody is a data to be packed in the Body part of the driver::TxDatagram
 */
struct DatagramBody {
  DatagramBody() = default;
  virtual ~DatagramBody() = default;
  DatagramBody(const DatagramBody& v) = default;
  DatagramBody& operator=(const DatagramBody& obj) = default;
  DatagramBody(DatagramBody&& obj) = default;
  DatagramBody& operator=(DatagramBody&& obj) = default;

  virtual std::unique_ptr<driver::Operation> operation(const Geometry& geometry) = 0;
};

/**
 * @brief DatagramHeader that does nothing
 */
struct NullHeader final : DatagramHeader {
  ~NullHeader() override = default;
  NullHeader() = default;
  NullHeader(const NullHeader& v) noexcept = default;
  NullHeader& operator=(const NullHeader& obj) = default;
  NullHeader(NullHeader&& obj) = default;
  NullHeader& operator=(NullHeader&& obj) = default;

  std::unique_ptr<driver::Operation> operation() override { return std::make_unique<driver::NullHeader>(); }
};

/**
 * @brief DatagramBody that does nothing
 */
struct NullBody final : DatagramBody {
  ~NullBody() override = default;
  NullBody() = default;
  NullBody(const NullBody& v) noexcept = default;
  NullBody& operator=(const NullBody& obj) = default;
  NullBody(NullBody&& obj) = default;
  NullBody& operator=(NullBody&& obj) = default;

  std::unique_ptr<driver::Operation> operation(const Geometry&) override { return std::make_unique<driver::NullBody>(); }
};

}  // namespace autd3::core
