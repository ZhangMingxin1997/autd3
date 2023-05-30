#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <cstdint>

namespace autd3::internal::native_methods {

enum class SyncMode : uint8_t {
  FreeRun = 0,
  DC = 1,
};

extern "C" {

[[nodiscard]] void* AUTDGetAdapterPointer(uint32_t *len);

void AUTDGetAdapter(void* adapters, uint32_t idx, char *desc, char *name);

void AUTDFreeAdapterPointer(void* adapters);

[[nodiscard]] void* AUTDLinkSOEM();

[[nodiscard]] void* AUTDLinkSOEMSendCycle(void* builder, uint16_t cycle);

[[nodiscard]] void* AUTDLinkSOEMSync0Cycle(void* builder, uint16_t cycle);

[[nodiscard]] void* AUTDLinkSOEMBufSize(void* builder, uint32_t buf_size);

[[nodiscard]] void* AUTDLinkSOEMTimerStrategy(void* builder, TimerStrategy timer_strategy);

[[nodiscard]] void* AUTDLinkSOEMSyncMode(void* builder, SyncMode mode);

[[nodiscard]] void* AUTDLinkSOEMIfname(void* builder, const char *ifname);

[[nodiscard]] void* AUTDLinkSOEMStateCheckInterval(void* builder, uint32_t interval_ms);

[[nodiscard]] void* AUTDLinkSOEMOnLost(void* builder, void* on_lost_func);

[[nodiscard]] void* AUTDLinkSOEMLogLevel(void* builder, Level level);

[[nodiscard]]
void* AUTDLinkSOEMLogFunc(void* builder,
                          Level level,
                          void* out_func,
                          void* flush_func);

[[nodiscard]] void* AUTDLinkSOEMTimeout(void* builder, uint64_t timeout_ns);

[[nodiscard]] void* AUTDLinkSOEMBuild(void* builder);

[[nodiscard]] void* AUTDLinkRemoteSOEM(const char *addr, uint16_t port);

[[nodiscard]] void* AUTDLinkRemoteSOEMTimeout(void* builder, uint64_t timeout_ns);

[[nodiscard]] void* AUTDLinkRemoteSOEMBuild(void* builder);

} // extern "C"

} // namespace autd3::internal::native_methods
