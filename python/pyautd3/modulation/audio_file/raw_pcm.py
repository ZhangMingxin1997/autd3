'''
File: raw_pcm.py
Project: audio_file
Created Date: 14/09/2023
Author: Shun Suzuki
-----
Last Modified: 14/09/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

'''


import ctypes
from datetime import timedelta

from pyautd3.native_methods.autd3capi_modulation_audio_file import (
    NativeMethods as ModulationAudioFile,
)
from pyautd3.native_methods.autd3capi_def import ModulationPtr, FPGA_SUB_CLK_FREQ
from pyautd3.autd_error import AUTDError

from pyautd3.internal.modulation import IModulation

from typing import Optional


class RawPCM(IModulation):
    _path: str
    _sample_rate: int
    _freq_div: Optional[int]

    def __init__(self, path: str, sample_rate: int):
        super().__init__()
        self._path = path
        self._sample_rate = sample_rate
        self._freq_div = None

    def with_sampling_frequency_division(self, div: int) -> "RawPCM":
        self._freq_div = div
        return self

    def with_sampling_frequency(self, freq: float) -> "RawPCM":
        div = int(FPGA_SUB_CLK_FREQ / freq)
        return self.with_sampling_frequency_division(div)

    def with_sampling_period(self, period: timedelta) -> "RawPCM":
        return self.with_sampling_frequency_division(int(FPGA_SUB_CLK_FREQ / 1000000000. * (period.total_seconds() * 1000. * 1000. * 1000.)))

    def modulation_ptr(self) -> ModulationPtr:
        err = ctypes.create_string_buffer(256)
        ptr = ModulationAudioFile().modulation_raw_pcm(self._path.encode("utf-8"), self._sample_rate, err)
        if ptr._0 is None:
            raise AUTDError(err)
        if self._freq_div is not None:
            ptr = ModulationAudioFile().modulation_raw_pcm_with_sampling_frequency_division(
                ptr, self._freq_div
            )
        return ptr
