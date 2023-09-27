// File: cache.cpp
// Project: gain
// Created Date: 26/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 26/09/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#include <autd3/gain/uniform.hpp>
#include <autd3/gain/gain.hpp>
#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Gain, Cache) {
  auto autd = create_controller();

  ASSERT_TRUE(autd.send(autd3::gain::Uniform(0.5).with_phase(autd3::internal::pi).with_cache()));

  for (auto& dev : autd.geometry()) {
    auto [duties, phases] = autd3::link::Audit::duties_and_phases(autd, dev.idx(), 0);
    ASSERT_TRUE(std::ranges::all_of(duties, [](auto d) { return d == 680; }));
    ASSERT_TRUE(std::ranges::all_of(phases, [](auto p) { return p == 2048; }));
  }
}

class ForCacheTest final : public autd3::gain::Gain {
 public:
  explicit ForCacheTest(size_t* cnt) : _cnt(cnt) {}

  [[nodiscard]] std::unordered_map<size_t, std::vector<autd3::internal::native_methods::Drive>> calc(const autd3::internal::Geometry& geometry) const override {
    ++(*_cnt);
    return transform(geometry, [&](const auto& dev, const auto& tr) { return autd3::internal::native_methods::Drive{0.0, 1.0}; });
  }

  AUTD3_IMPL_WITH_CACHE_GAIN(ForCacheTest)

 private:
  size_t* _cnt;
};

TEST(Gain, CacheCheckOnce) {
  auto autd = create_controller();

  {
    size_t cnt = 0;
    ForCacheTest g(&cnt);
    ASSERT_TRUE(autd.send(g));
    ASSERT_EQ(cnt, 1);
    ASSERT_TRUE(autd.send(g));
    ASSERT_EQ(cnt, 2);
  }

  {
    size_t cnt = 0;
    ForCacheTest g(&cnt);
    auto gc = g.with_cache();
    ASSERT_TRUE(autd.send(gc));
    ASSERT_EQ(cnt, 1);
    ASSERT_TRUE(autd.send(gc));
    ASSERT_EQ(cnt, 1);
  }
}
