// File: primitive.hpp
// Project: gain
// Created Date: 10/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 10/09/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <utility>
#include <vector>

#include "autd3/core/gain.hpp"

namespace autd3::gain {

/**
 * @brief Gain to produce nothing
 */
class Null final : public core::Gain {
 public:
  Null() noexcept {}

  void calc(const core::Geometry& geometry) override {
    std::for_each(geometry.begin(), geometry.end(), [this](const auto& dev) {
      std::for_each(dev.begin(), dev.end(), [this](const auto& trans) {
        _drives[trans.id()].amp = 0.0;
        _drives[trans.id()].phase = 0.0;
      });
    });
  }

  ~Null() override = default;
  Null(const Null& v) noexcept = default;
  Null& operator=(const Null& obj) = default;
  Null(Null&& obj) = default;
  Null& operator=(Null&& obj) = default;
};

/**
 * @brief Gain to produce single focal point
 */
class Focus final : public core::Gain {
 public:
  /**
   * @param[in] point focal point
   * @param[in] amp amplitude of the focus (from 0.0 to 1.0)
   */
  explicit Focus(core::Vector3 point, const double amp = 1.0) : _point(std::move(point)), _amp(amp) {}

  void calc(const core::Geometry& geometry) override {
    std::for_each(geometry.begin(), geometry.end(), [&](const auto& dev) {
      std::for_each(dev.begin(), dev.end(), [&](const auto& transducer) {
        const auto dist = (_point - transducer.position()).norm();
        const auto phase = transducer.align_phase_at(dist, geometry.sound_speed);
        _drives[transducer.id()].amp = _amp;
        _drives[transducer.id()].phase = phase;
      });
    });
  }

  ~Focus() override = default;
  Focus(const Focus& v) noexcept = default;
  Focus& operator=(const Focus& obj) = default;
  Focus(Focus&& obj) = default;
  Focus& operator=(Focus&& obj) = default;

 private:
  core::Vector3 _point;
  double _amp;
};

/**
 * @brief Gain to produce Bessel Beam
 */
class BesselBeam final : public core::Gain {
 public:
  /**
   * @param[in] apex apex of the conical wavefront of the beam
   * @param[in] vec_n direction of the beam
   * @param[in] theta_z angle between the side of the cone and the plane perpendicular to direction of the beam
   * @param[in] amp amplitude of the wave (from 0.0 to 1.0)
   */
  explicit BesselBeam(core::Vector3 apex, core::Vector3 vec_n, const double theta_z, const double amp = 1.0)
      : core::Gain(), _apex(std::move(apex)), _vec_n(std::move(vec_n)), _theta_z(theta_z), _amp(amp) {}

  void calc(const core::Geometry& geometry) override {
    _vec_n.normalize();
    core::Vector3 v = core::Vector3::UnitZ().cross(_vec_n);
    const auto theta_v = std::asin(v.norm());
    v.normalize();
    const Eigen::AngleAxisd rot(-theta_v, v);

    std::for_each(geometry.begin(), geometry.end(), [&](const auto& dev) {
      std::for_each(dev.begin(), dev.end(), [&](const auto& transducer) {
        const auto r = transducer.position() - this->_apex;
        const auto rr = rot * r;
        const auto d = std::sin(_theta_z) * std::sqrt(rr.x() * rr.x() + rr.y() * rr.y()) - std::cos(_theta_z) * rr.z();
        const auto phase = transducer.align_phase_at(d, geometry.sound_speed);
        _drives[transducer.id()].amp = _amp;
        _drives[transducer.id()].phase = phase;
      });
    });
  }

  ~BesselBeam() override = default;
  BesselBeam(const BesselBeam& v) noexcept = default;
  BesselBeam& operator=(const BesselBeam& obj) = default;
  BesselBeam(BesselBeam&& obj) = default;
  BesselBeam& operator=(BesselBeam&& obj) = default;

 private:
  core::Vector3 _apex;
  core::Vector3 _vec_n;
  double _theta_z;
  double _amp;
};

/**
 * @brief Gain to create plane wave
 */
class PlaneWave final : public core::Gain {
 public:
  /**
   * @param[in] direction wave direction
   * @param[in] amp amplitude of the wave (from 0.0 to 1.0)
   */
  explicit PlaneWave(core::Vector3 direction, const double amp = 1.0) noexcept : _direction(std::move(direction)), _amp(amp) {}

  void calc(const core::Geometry& geometry) override {
    std::for_each(geometry.begin(), geometry.end(), [&](const auto& dev) {
      std::for_each(dev.begin(), dev.end(), [&](const auto& transducer) {
        const auto dist = transducer.position().dot(_direction);
        const auto phase = transducer.align_phase_at(dist, geometry.sound_speed);
        _drives[transducer.id()].amp = _amp;
        _drives[transducer.id()].phase = phase;
      });
    });
  }

  ~PlaneWave() override = default;
  PlaneWave(const PlaneWave& v) noexcept = default;
  PlaneWave& operator=(const PlaneWave& obj) = default;
  PlaneWave(PlaneWave&& obj) = default;
  PlaneWave& operator=(PlaneWave&& obj) = default;

 private:
  core::Vector3 _direction;
  double _amp;
};

/**
 * @brief Gain to group some gains
 */
class Grouped final : public core::Gain {
 public:
  /**
   * \brief Decide which device outputs which Gain
   * \param device_id device id
   * \param gain gain
   */
  template <class G>
  std::enable_if_t<std::is_base_of_v<core::Gain, G>> add(const size_t device_id, G& gain) {
    gain.build(_geometry);
    if (device_id < _geometry.num_devices())
      std::memcpy(_buf.data() + device_id * driver::NUM_TRANS_IN_UNIT, gain.drives().data() + device_id * driver::NUM_TRANS_IN_UNIT,
                  sizeof(driver::Drive) * driver::NUM_TRANS_IN_UNIT);
  }

  void calc(const core::Geometry& geometry) override { std::memcpy(_drives.data(), _buf.data(), geometry.num_transducers() * sizeof(driver::Drive)); }

  explicit Grouped(const core::Geometry& geometry) : core::Gain(), _buf(), _geometry(geometry) {
    _buf.resize(geometry.num_transducers(), driver::Drive{0, 0, 0});
  }
  ~Grouped() override = default;
  Grouped(const Grouped& v) noexcept = delete;
  Grouped& operator=(const Grouped& obj) = delete;
  Grouped(Grouped&& obj) = delete;
  Grouped& operator=(Grouped&& obj) = delete;

 private:
  std::vector<driver::Drive> _buf;
  const core::Geometry& _geometry;
};

/**
 * @brief Gain to drive a tranducer
 */
class TransducerTest final : public core::Gain {
 public:
  /**
   * @param[in] dev_idx device index
   * @param[in] tr_idx local transducer index
   * @param[in] amp amplitude (from 0.0 to 1.0)
   * @param[in] phase phase in radian
   */
  explicit TransducerTest(const size_t dev_idx, const size_t tr_idx, const double amp, const double phase) noexcept
      : _dev_idx(dev_idx), _tr_idx(tr_idx), _amp(amp), _phase(phase) {}

  /**
   * @param[in] tr_idx global transducer index
   * @param[in] amp amplitude (from 0.0 to 1.0)
   * @param[in] phase phase in radian
   */
  explicit TransducerTest(const size_t tr_idx, const double amp, const double phase) noexcept
      : TransducerTest(tr_idx / autd3::driver::NUM_TRANS_IN_UNIT, tr_idx % autd3::driver::NUM_TRANS_IN_UNIT, amp, phase) {}

  void calc(const core::Geometry& geometry) override {
    const auto id = geometry[_dev_idx][_tr_idx].id();
    _drives[id].amp = _amp;
    _drives[id].phase = _phase / (2.0 * autd3::driver::pi);
  }

  ~TransducerTest() override = default;
  TransducerTest(const TransducerTest& v) noexcept = default;
  TransducerTest& operator=(const TransducerTest& obj) = default;
  TransducerTest(TransducerTest&& obj) = default;
  TransducerTest& operator=(TransducerTest&& obj) = default;

 private:
  size_t _dev_idx;
  size_t _tr_idx;
  double _amp;
  double _phase;
};

}  // namespace autd3::gain
