// File: datagram.hpp
// Project: internal
// Created Date: 29/05/2023
// Author: Shun Suzuki
// -----
// Last Modified: 24/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include <type_traits>

#include "autd3/internal/geometry/geometry.hpp"
#include "autd3/internal/native_methods.hpp"
#include "autd3/internal/utils.hpp"

namespace autd3::internal {

class SpecialDatagram {
 public:
  SpecialDatagram() = default;
  SpecialDatagram(const SpecialDatagram& obj) = default;
  SpecialDatagram& operator=(const SpecialDatagram& obj) = default;
  SpecialDatagram(SpecialDatagram&& obj) = default;
  SpecialDatagram& operator=(SpecialDatagram&& obj) = default;
  virtual ~SpecialDatagram() = default;

  [[nodiscard]] virtual native_methods::DatagramSpecialPtr ptr() const = 0;
};

template <typename S>
using is_special = std::is_base_of<SpecialDatagram, std::remove_reference_t<S>>;

template <typename S>
constexpr bool is_special_v = is_special<S>::value;

class Datagram {
 public:
  Datagram() = default;
  Datagram(const Datagram& v) noexcept = default;
  Datagram& operator=(const Datagram& obj) = default;
  Datagram(Datagram&& obj) = default;
  Datagram& operator=(Datagram&& obj) = default;
  virtual ~Datagram() = default;

  [[nodiscard]] virtual native_methods::DatagramPtr ptr(const Geometry& geometry) const = 0;
};

template <typename D>
using is_datagram = std::is_base_of<Datagram, std::remove_reference_t<D>>;

template <typename D>
constexpr bool is_datagram_v = is_datagram<D>::value;

class NullDatagram final : public Datagram {
 public:
  NullDatagram() = default;
  ~NullDatagram() override = default;
  NullDatagram(const NullDatagram& v) noexcept = default;
  NullDatagram& operator=(const NullDatagram& obj) = default;
  NullDatagram(NullDatagram&& obj) = default;
  NullDatagram& operator=(NullDatagram&& obj) = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override { return native_methods::DatagramPtr{nullptr}; }
};

/**
 * @brief Datagram to configure silencer
 */
class Silencer final : public Datagram {
 public:
  Silencer() noexcept : Silencer(256, 256) {}
  /**
   * @brief Constructor
   *
   * @param step_intensity Intensity update step of silencer. The smaller `step` is, the quieter the output is.
   * @param step_phase Phase update step of silencer. The smaller `step` is, the quieter the output is.
   */
  explicit Silencer(const uint16_t step_intensity, const uint16_t step_phase) noexcept
      : Datagram(), _step_intensity(step_intensity), _step_phase(step_phase) {}

  /**
   * @brief Disable silencer
   */
  static Silencer disable() noexcept { return Silencer(0xFFFF, 0xFFFF); }

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override {
    return validate(native_methods::AUTDDatagramSilencer(_step_intensity, _step_phase));
  }

 private:
  uint16_t _step_intensity;
  uint16_t _step_phase;
};

/**
 * @brief Datagram to set modulation delay
 */
class ConfigureModDelay final : public Datagram {
 public:
  ConfigureModDelay() = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override { return native_methods::AUTDDatagramConfigureModDelay(); }
};

/**
 * @brief Datagram for clear all data in devices
 */
class Clear final : public Datagram {
 public:
  Clear() = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override { return native_methods::AUTDDatagramClear(); }
};

/**
 * @brief Datagram to update flags (Force fan flag and reads FPGA info flag)
 */
class UpdateFlags final : public Datagram {
 public:
  UpdateFlags() = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override { return native_methods::AUTDDatagramUpdateFlags(); }
};

/**
 * @brief Datagram to synchronize devices
 */
class Synchronize final : public Datagram {
 public:
  Synchronize() = default;

  [[nodiscard]] native_methods::DatagramPtr ptr(const Geometry&) const override { return native_methods::AUTDDatagramSynchronize(); }
};

}  // namespace autd3::internal
