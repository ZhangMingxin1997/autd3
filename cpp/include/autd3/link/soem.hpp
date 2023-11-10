// File: soem.hpp
// Project: link
// Created Date: 29/05/2023
// Author: Shun Suzuki
// -----
// Last Modified: 11/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
//

#pragma once

#include <chrono>
#include <string>

#include "autd3/internal/exception.hpp"
#include "autd3/internal/link.hpp"
#include "autd3/internal/native_methods.hpp"

namespace autd3::link {

using internal::native_methods::SyncMode;

using OnErrCallback = void (*)(const char* msg);

/**
 * @brief Link using [SOEM](https://github.com/OpenEtherCATsociety/SOEM)
 *
 */
class SOEM {
 public:
  class Builder final : public internal::LinkBuilder {
    friend class SOEM;

    internal::native_methods::LinkSOEMBuilderPtr _ptr;

    Builder() : LinkBuilder(), _ptr(internal::native_methods::AUTDLinkSOEM()) {}

   public:
    [[nodiscard]] internal::native_methods::LinkBuilderPtr ptr() const override { return AUTDLinkSOEMIntoBuilder(_ptr); }

    /**
     * @brief Set network interface name
     * @details If empty, this link will automatically find the network interface that is connected to AUTD3 devices.
     *
     * @param ifname Network interface name
     * @return Builder
     */
    Builder with_ifname(const std::string& ifname) {
      _ptr = AUTDLinkSOEMWithIfname(_ptr, ifname.c_str());
      return *this;
    }

    /**
     * @brief Set buffer size
     *
     * @param value
     * @return Builder
     */
    Builder with_buf_size(const size_t value) {
      _ptr = AUTDLinkSOEMWithBufSize(_ptr, static_cast<uint32_t>(value));
      return *this;
    }

    /**
     * @brief Set send cycle (the unit is 500us)
     *
     * @param value
     * @return Builder
     */
    Builder with_send_cycle(const uint16_t value) {
      _ptr = AUTDLinkSOEMWithSendCycle(_ptr, value);
      return *this;
    }

    /**
     * @brief Set sync0 cycle (the unit is 500us)
     *
     * @param value
     * @return Builder
     */
    Builder with_sync0_cycle(const uint16_t value) {
      _ptr = AUTDLinkSOEMWithSync0Cycle(_ptr, value);
      return *this;
    }

    /**
     * @brief Set callback function when the link is lost
     *
     * @param value
     * @return Builder
     */
    Builder with_on_lost(const OnErrCallback value) {
      _ptr = AUTDLinkSOEMWithOnLost(_ptr, reinterpret_cast<void*>(value));
      return *this;
    }
    /**
     * @brief Set callback function when some errors occur
     *
     * @param value
     * @return Builder
     */
    Builder with_on_err(const OnErrCallback value) {
      _ptr = AUTDLinkSOEMWithOnErr(_ptr, reinterpret_cast<void*>(value));
      return *this;
    }

    /**
     * @brief Set timer strategy
     *
     * @param value
     * @return Builder
     */
    Builder with_timer_strategy(const internal::native_methods::TimerStrategy value) {
      _ptr = AUTDLinkSOEMWithTimerStrategy(_ptr, value);
      return *this;
    }

    /**
     * @brief Set sync mode
     * @details See [Beckhoff's site](https://infosys.beckhoff.com/content/1033/ethercatsystem/2469122443.html) for more details.
     *
     * @param value
     * @return Builder
     */
    Builder with_sync_mode(const SyncMode value) {
      _ptr = AUTDLinkSOEMWithSyncMode(_ptr, value);
      return *this;
    }

    /**
     * @brief Set state check interval
     *
     * @param value
     * @return Builder
     */
    template <typename Rep, typename Period>
    Builder with_state_check_interval(const std::chrono::duration<Rep, Period> value) {
      const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(value).count();
      _ptr = AUTDLinkSOEMWithStateCheckInterval(_ptr, static_cast<uint32_t>(ms));
      return *this;
    }

    template <typename Rep, typename Period>
    Builder with_timeout(const std::chrono::duration<Rep, Period> timeout) {
      const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(timeout).count();
      _ptr = AUTDLinkSOEMWithTimeout(_ptr, static_cast<uint64_t>(ns));
      return *this;
    }
  };

  static Builder builder() { return {}; }

  SOEM() = delete;
};

/**
 * @brief Link to connect to remote SOEMServer
 */
class RemoteSOEM final {
 public:
  class Builder final : public internal::LinkBuilder {
    friend class RemoteSOEM;

    internal::native_methods::LinkRemoteSOEMBuilderPtr _ptr;

    explicit Builder(const std::string& addr) : LinkBuilder() {
      auto [result, err_len, err] = internal::native_methods::AUTDLinkRemoteSOEM(addr.c_str());
      if (result._0 == nullptr) {
        const std::string err_str(err_len, ' ');
        internal::native_methods::AUTDGetErr(err, const_cast<char*>(err_str.c_str()));
        throw internal::AUTDException(err_str);
      }
      _ptr = result;
    }

   public:
    [[nodiscard]] internal::native_methods::LinkBuilderPtr ptr() const override { return AUTDLinkRemoteSOEMIntoBuilder(_ptr); }

    template <typename Rep, typename Period>
    Builder with_timeout(const std::chrono::duration<Rep, Period> timeout) {
      const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(timeout).count();
      _ptr = AUTDLinkRemoteSOEMWithTimeout(_ptr, static_cast<uint64_t>(ns));
      return std::move(*this);
    }
  };

  /**
   * @brief Constructor
   *
   * @param addr IP address and port of SOEMServer (e.g., "127.0.0.1:8080")
   */
  static Builder builder(const std::string& addr) { return Builder(addr); }

  RemoteSOEM() = delete;
};

}  // namespace autd3::link
