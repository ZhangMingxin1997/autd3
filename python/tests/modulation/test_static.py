'''
File: test_static.py
Project: modulation
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

'''


from ..test_autd import create_controller

from pyautd3.modulation import Static

import numpy as np


def test_static():
    autd = create_controller()

    assert autd.send(Static().with_amp(0.2))

    for dev in autd.geometry:
        mod = autd.link.modulation(dev.idx)
        mod_expext = [32, 32]
        assert np.array_equal(mod, mod_expext)
        assert autd.link.modulation_frequency_division(dev.idx) == 40960
