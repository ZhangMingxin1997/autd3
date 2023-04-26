// File: acoustics.hpp
// Project: core
// Created Date: 11/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 25/04/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <cmath>
#include <complex>

#include "autd3/driver/defined.hpp"

namespace autd3::core {

#ifdef AUTD3_USE_SINGLE_FLOAT
constexpr driver::float_t DIR_COEFFICIENT_A[] = {1.0f,         1.0f,         1.0f,         0.891250938f, 0.707945784f,
                                                       0.501187234f, 0.354813389f, 0.251188643f, 0.199526231f};
constexpr driver::float_t DIR_COEFFICIENT_B[] = {
    0.f, 0.f, -0.00459648054721f, -0.0155520765675f, -0.0208114779827f, -0.0182211227016f, -0.0122437497109f, -0.00780345575475f, -0.00312857467007f};
constexpr driver::float_t DIR_COEFFICIENT_C[] = {0.f,
                                                       0.f,
                                                       -0.000787968093807f,
                                                       -0.000307591508224f,
                                                       -0.000218348633296f,
                                                       0.00047738416141f,
                                                       0.000120353137658f,
                                                       0.000323676257958f,
                                                       0.000143850511f};
constexpr driver::float_t DIR_COEFFICIENT_D[] = {0.f,
                                                       0.f,
                                                       1.60125528528e-05f,
                                                       2.9747624976e-06f,
                                                       2.31910931569e-05f,
                                                       -1.1901034125e-05f,
                                                       6.77743734332e-06f,
                                                       -5.99548024824e-06f,
                                                       -4.79372835035e-06f};
#else
constexpr driver::float_t DIR_COEFFICIENT_A[] = {1.0, 1.0, 1.0, 0.891250938, 0.707945784, 0.501187234, 0.354813389, 0.251188643, 0.199526231};
constexpr driver::float_t DIR_COEFFICIENT_B[] = {
    0., 0., -0.00459648054721, -0.0155520765675, -0.0208114779827, -0.0182211227016, -0.0122437497109, -0.00780345575475, -0.00312857467007};
constexpr driver::float_t DIR_COEFFICIENT_C[] = {
    0., 0., -0.000787968093807, -0.000307591508224, -0.000218348633296, 0.00047738416141, 0.000120353137658, 0.000323676257958, 0.000143850511};
constexpr driver::float_t DIR_COEFFICIENT_D[] = {
    0., 0., 1.60125528528e-05, 2.9747624976e-06, 2.31910931569e-05, -1.1901034125e-05, 6.77743734332e-06, -5.99548024824e-06, -4.79372835035e-06};
#endif

using directivity_func = driver::float_t(driver::float_t);

/**
 * \brief Utility class to calculate directivity of ultrasound transducer.
 */
class Directivity {
 public:
  /**
   * \brief Directivity of T4010A1
   * \param theta_deg zenith angle in degree
   * \return directivity
   */
  static driver::float_t t4010a1(driver::float_t theta_deg) {
    theta_deg = std::abs(theta_deg);
    if (theta_deg > 90) return 0;
    const auto i = static_cast<size_t>(std::ceil(theta_deg / 10));
    if (i == 0) return 1;
    const auto a = DIR_COEFFICIENT_A[i - 1];
    const auto b = DIR_COEFFICIENT_B[i - 1];
    const auto c = DIR_COEFFICIENT_C[i - 1];
    const auto d = DIR_COEFFICIENT_D[i - 1];
    const auto x = theta_deg - static_cast<driver::float_t>(i - 1) * 10;
    return a + (b + (c + d * x) * x) * x;
  }

  static constexpr driver::float_t sphere(driver::float_t) noexcept { return 1.0; }  // NOLINT
};

/**
 * @brief Calculate complex sound pressure propagation
 * @param source_pos source transducer position
 * @param source_dir source transducer direction
 * @param attenuation attenuation coefficient
 * @param wavenumber wave number
 * @param target target position
 * @return complex sound pressure at target position
 */
template <directivity_func D = Directivity::sphere>
std::complex<driver::float_t> propagate(const driver::Vector3& source_pos, const driver::Vector3& source_dir,
                                              const driver::float_t attenuation, const driver::float_t wavenumber,
                                              const driver::Vector3& target) {
  const auto diff = target - source_pos;
  const auto dist = diff.norm();

  const auto theta = std::atan2(source_dir.cross(diff).norm(), source_dir.dot(diff)) * 180 / driver::pi;

  const auto d = D(theta);
  const auto r = d * std::exp(-dist * attenuation) / dist;
  const auto phi = -wavenumber * dist;
  return r * std::complex<driver::float_t>(std::cos(phi), std::sin(phi));
}

}  // namespace autd3::core
