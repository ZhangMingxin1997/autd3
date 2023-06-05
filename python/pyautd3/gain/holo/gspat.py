"""
File: gspat.py
Project: holo
Created Date: 21/10/2022
Author: Shun Suzuki
-----
Last Modified: 28/05/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.

"""


import numpy as np
from typing import Optional

from .backend import Backend
from .constraint import AmplitudeConstraint

from pyautd3.native_methods.autd3capi_gain_holo import NativeMethods as GainHolo
from pyautd3.native_methods.autd3capi_def import GainPtr
from pyautd3.geometry import Geometry

from .holo import Holo


class GSPAT(Holo):
    _repeat: Optional[int]
    _constraint: Optional[AmplitudeConstraint]

    def __init__(self):
        super().__init__()
        self._repeat = None
        self._constraint = None

    def with_repeat(self, value: int) -> "GSPAT":
        self._repeat = value
        return self

    def with_backend(self, backend: Backend) -> "GSPAT":
        self._backend = backend
        return self

    def with_constraint(self, constraint: AmplitudeConstraint) -> "GSPAT":
        self._constraint = constraint
        return self

    def gain_ptr(self, geometry: Geometry) -> GainPtr:
        size = len(self._amps)
        foci_ = np.ctypeslib.as_ctypes(np.array(self._foci).astype(np.double))
        amps = np.ctypeslib.as_ctypes(np.array(self._amps).astype(np.double))
        ptr = GainHolo().gain_holo_gspat(self._backend.ptr(), foci_, amps, size)
        if self._repeat is not None:
            ptr = GainHolo().gain_holo_gspat_with_repeat(ptr, self._repeat)
        if self._constraint is not None:
            ptr = GainHolo().gain_holo_gspat_with_constraint(
                ptr, self._constraint.ptr()
            )
        return ptr
