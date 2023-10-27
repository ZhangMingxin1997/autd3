"""
File: custom.py
Project: samples
Created Date: 11/10/2021
Author: Shun Suzuki
-----
Last Modified: 21/09/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.

"""


import numpy as np

from pyautd3 import Controller, Drive, Geometry, Silencer
from pyautd3.gain import Gain
from pyautd3.modulation import Modulation


class Focus(Gain):
    def __init__(self: "Focus", point: np.ndarray) -> None:
        self.point = np.array(point)

    def calc(self: "Focus", geometry: Geometry) -> dict[int, np.ndarray]:
        return Gain._transform(
            geometry,
            lambda dev, tr: Drive(
                np.linalg.norm(tr.position - self.point) * tr.wavenumber(dev.sound_speed),
                1.0,
            ),
        )


class Burst(Modulation):
    _length: int

    def __init__(self: "Burst", length: int, freq_div: int = 5120) -> None:
        super().__init__(freq_div)
        self._length = length

    def calc(self: "Burst") -> np.ndarray:
        buf = np.zeros(self._length, dtype=np.float64)
        buf[0] = 1
        return buf


def custom(autd: Controller) -> None:
    config = Silencer()
    autd.send(config)

    f = Focus(autd.geometry.center + np.array([0.0, 0.0, 150.0]))
    m = Burst(4000)

    autd.send(m, f)
