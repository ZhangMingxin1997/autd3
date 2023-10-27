#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <cstdint>

namespace autd3::internal::native_methods {

struct LinkSimulatorBuilderPtr {
  void* _0;
};

extern "C" {

[[nodiscard]] LinkSimulatorBuilderPtr AUTDLinkSimulator(uint16_t port);

[[nodiscard]]
LinkSimulatorBuilderPtr AUTDLinkSimulatorWithAddr(LinkSimulatorBuilderPtr simulator,
                                                  const char *addr,
                                                  char *err);

[[nodiscard]]
LinkSimulatorBuilderPtr AUTDLinkSimulatorWithTimeout(LinkSimulatorBuilderPtr simulator,
                                                     uint64_t timeout_ns);

[[nodiscard]] LinkBuilderPtr AUTDLinkSimulatorIntoBuilder(LinkSimulatorBuilderPtr simulator);

[[nodiscard]]
int32_t AUTDLinkSimulatorUpdateGeometry(LinkPtr simulator,
                                        GeometryPtr geometry,
                                        char *err);

} // extern "C"

} // namespace autd3::internal::native_methods
