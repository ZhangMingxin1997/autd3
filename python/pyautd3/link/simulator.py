"""
File: simulator.py
Project: link
Created Date: 21/10/2022
Author: Shun Suzuki
-----
Last Modified: 25/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.

"""


import asyncio
import ctypes
from datetime import timedelta

from pyautd3.autd_error import AUTDError
from pyautd3.geometry import Geometry
from pyautd3.internal.link import Link, LinkBuilder
from pyautd3.native_methods.autd3capi import NativeMethods as Base
from pyautd3.native_methods.autd3capi_def import AUTD3_ERR, ControllerPtr, LinkPtr
from pyautd3.native_methods.autd3capi_def import NativeMethods as Def
from pyautd3.native_methods.autd3capi_link_simulator import (
    LinkBuilderPtr,
    LinkSimulatorBuilderPtr,
)
from pyautd3.native_methods.autd3capi_link_simulator import (
    NativeMethods as LinkSimulator,
)


class Simulator(Link):
    """Link for Simulator."""

    _ptr: LinkPtr

    class _Builder(LinkBuilder):
        _builder: LinkSimulatorBuilderPtr

        def __init__(self: "Simulator._Builder", port: int) -> None:
            self._builder = LinkSimulator().link_simulator(port)

        def with_server_ip(self: "Simulator._Builder", addr: str) -> "Simulator._Builder":
            """Set server IP address.

            Arguments:
            ---------
                addr: Server IP address
            """
            result = LinkSimulator().link_simulator_with_addr(self._builder, addr.encode("utf-8"))
            if result.result._0 is None:
                err = ctypes.create_string_buffer(int(result.err_len))
                Def().get_err(result.err, err)
                raise AUTDError(err)
            self._builder = result.result
            return self

        def with_timeout(self: "Simulator._Builder", timeout: timedelta) -> "Simulator._Builder":
            """Set timeout.

            Arguments:
            ---------
                timeout: Timeout
            """
            self._builder = LinkSimulator().link_simulator_with_timeout(self._builder, int(timeout.total_seconds() * 1000 * 1000 * 1000))
            return self

        def _link_builder_ptr(self: "Simulator._Builder") -> LinkBuilderPtr:
            return LinkSimulator().link_simulator_into_builder(self._builder)

        def _resolve_link(self: "Simulator._Builder", ptr: ControllerPtr) -> "Simulator":
            return Simulator(Base().link_get(ptr))

    def __init__(self: "Simulator", ptr: LinkPtr) -> None:
        super().__init__(ptr)

    @staticmethod
    def builder(port: int) -> _Builder:
        """Create Simulator link builder."""
        return Simulator._Builder(port)

    async def update_geometry_async(self: "Simulator", geometry: Geometry) -> None:
        """Update geometry."""
        future: asyncio.Future = asyncio.Future()
        loop = asyncio.get_event_loop()
        loop.call_soon(
            lambda *_: future.set_result(
                LinkSimulator().link_simulator_update_geometry(
                    self._ptr,
                    geometry._geometry_ptr(),
                ),
            ),
        )
        res = await future
        result = int(res.result)
        if result == AUTD3_ERR:
            err = ctypes.create_string_buffer(int(res.err_len))
            Def().get_err(res.err, err)
            raise AUTDError(err)
