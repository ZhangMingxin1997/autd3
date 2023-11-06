"""
File: test_modulation.py
Project: modulation
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

"""


import numpy as np

from pyautd3.modulation import Modulation
from tests.test_autd import create_controller


class Burst(Modulation):
    def __init__(self: "Burst") -> None:
        super().__init__(5120)

    def calc(self: "Burst"):
        buf = np.zeros(10, dtype=np.float64)
        buf[0] = 1
        return buf


def test_modulation():
    autd = create_controller()

    m = Burst()

    assert m.sampling_frequency_division == 5120
    assert m.sampling_frequency == 4000
    assert len(m) == 10

    assert autd.send(m)

    for dev in autd.geometry:
        mod = autd.link.modulation(dev.idx)
        assert len(mod) == 10
        assert mod[0] == 0xFF
        assert np.all(mod[1:] == 0)
        assert autd.link.modulation_frequency_division(dev.idx) == 5120
