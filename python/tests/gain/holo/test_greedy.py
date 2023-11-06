"""
File: test_greedy.py
Project: holo
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

"""


import numpy as np

from pyautd3 import AUTD3, Controller
from pyautd3.gain.holo import AmplitudeConstraint, Greedy
from pyautd3.link.audit import Audit


def test_greedy():
    autd = Controller[Audit].builder().add_device(AUTD3.from_euler_zyz([0.0, 0.0, 0.0], [0.0, 0.0, 0.0])).open_with(Audit.builder())

    g = (
        Greedy()
        .add_focus(autd.geometry.center + np.array([30, 0, 150]), 0.5)
        .add_foci_from_iter((autd.geometry.center + np.array([0, x, 150]), 0.5) for x in [-30])
        .with_phase_div(16)
        .with_constraint(AmplitudeConstraint.uniform(0.5))
    )
    assert autd.send(g)

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 85)
        assert not np.all(phases == 0)
