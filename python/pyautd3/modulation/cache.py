"""
File: cache.py
Project: modulation
Created Date: 10/10/2023
Author: Shun Suzuki
-----
Last Modified: 10/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

"""


from collections.abc import Iterator
from ctypes import create_string_buffer
from typing import TypeVar

import numpy as np

from pyautd3.autd_error import AUTDError
from pyautd3.internal.modulation import IModulation
from pyautd3.native_methods.autd3capi import NativeMethods as Base
from pyautd3.native_methods.autd3capi import ResultCache
from pyautd3.native_methods.autd3capi_def import ModulationPtr
from pyautd3.native_methods.autd3capi_def import NativeMethods as Def

M = TypeVar("M", bound=IModulation)


class Cache(IModulation):
    """Modulation to cache the result of calculation."""

    _cache: ResultCache
    _buffer: np.ndarray

    def __init__(self: "Cache", m: M) -> None:
        cache = Base().modulation_with_cache(m._modulation_ptr())
        if cache.result is None:
            err = create_string_buffer(int(cache.err_len))
            Def().get_err(cache.err, err)
            raise AUTDError(err)
        self._cache = cache
        n = int(self._cache.buffer_len)
        self._buffer = np.zeros(n, dtype=float)
        Base().modulation_cache_get_buffer(self._cache, np.ctypeslib.as_ctypes(self._buffer))

    @property
    def buffer(self: "Cache") -> np.ndarray:
        """Get cached modulation data."""
        return self._buffer

    def __getitem__(self: "Cache", key: int) -> float:
        return self._buffer[key]

    def __iter__(self: "Cache") -> Iterator[float]:
        return iter(self._buffer)

    def _modulation_ptr(self: "Cache") -> ModulationPtr:
        return Base().modulation_cache_into_modulation(self._cache)

    def __del__(self: "Cache") -> None:
        Base().modulation_cache_delete(self._cache)


def __with_cache(self: M) -> Cache:
    """Cache the result of calculation."""
    return Cache(self)


IModulation.with_cache = __with_cache  # type: ignore[method-assign]
