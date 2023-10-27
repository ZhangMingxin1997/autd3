"""
File: test_null.py
Project: gain
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

"""


import numpy as np

from pyautd3.gain import Null

from ..test_autd import create_controller


def test_null():
    autd = create_controller()

    assert autd.send(Null())

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 8)
        assert np.all(phases == 0)
