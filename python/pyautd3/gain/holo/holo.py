"""
File: holo.py
Project: holo
Created Date: 05/06/2023
Author: Shun Suzuki
-----
Last Modified: 05/06/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

"""

import numpy as np
from typing import List, Optional

from pyautd3.gain.gain import IGain
from .backend import Backend


class Holo(IGain):
    _foci: List[float]
    _amps: List[float]
    _backend: Optional[Backend]

    def __init__(self, backend: Backend = None):
        self._foci = []
        self._amps = []
        self._backend = backend

    def add_focus(self, focus: np.ndarray, amp: float):
        self._foci.append(focus[0])
        self._foci.append(focus[1])
        self._foci.append(focus[2])
        self._amps.append(amp)
