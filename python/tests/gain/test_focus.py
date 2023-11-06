"""
File: test_focus.py
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

from pyautd3.gain import Focus
from tests.test_autd import create_controller


def test_focus():
    autd = create_controller()

    assert autd.send(Focus(autd.geometry.center).with_amp(0.5))

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 85)
        assert not np.all(phases == 0)
