"""
File: evp.py
Project: holo
Created Date: 21/10/2022
Author: Shun Suzuki
-----
Last Modified: 28/05/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.

"""


from .holo import Holo
from .backend import Backend

from pyautd3.native_methods.autd3capi_gain_holo import NativeMethods as GainHolo


class EVP(Holo):
    def __init__(self, backend: Backend):
        super().__init__()
        self.ptr = GainHolo().gain_holo_evp(backend.ptr)

    def gamma(self, gamma: float):
        GainHolo().gain_holo_evp_gamma(self.ptr, gamma)

    def __del__(self):
        super().__del__()
