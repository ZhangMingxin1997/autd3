'''
File: test_bessel.py
Project: gain
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 20/09/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

'''

from ..test_autd import create_controller

from pyautd3.gain import Bessel
from pyautd3.link.audit import Audit

import numpy as np


def test_bessel():
    autd = create_controller()

    assert autd.send(Bessel(autd.geometry.center, [0, 0, 1], np.pi / 4).with_amp(0.5))

    for dev in autd.geometry:
        duties, phases = Audit.duties_and_phases(autd._ptr, dev.idx, 0)
        assert np.all(duties == 680)
        assert not np.all(phases == 0)
