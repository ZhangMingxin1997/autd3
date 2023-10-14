'''
File: test_evp.py
Project: holo
Created Date: 20/09/2023
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2023 Shun Suzuki. All rights reserved.

'''


from pyautd3 import AUTD3, Controller
import pytest

from pyautd3.gain.holo import NalgebraBackend, EVP, AmplitudeConstraint
from pyautd3.gain.holo.backend_cuda import CUDABackend
from pyautd3.link.audit import Audit

import numpy as np


def test_evp():
    autd = Controller.builder()\
        .add_device(AUTD3.from_euler_zyz([0.0, 0.0, 0.0], [0.0, 0.0, 0.0]))\
        .open_with(Audit.builder())

    backend = NalgebraBackend()
    g = EVP(backend)\
        .add_focus(autd.geometry.center + np.array([30, 0, 150]), 0.5)\
        .add_foci_from_iter(map(lambda x: (autd.geometry.center + np.array([0, x, 150]), 0.5), [-30]))\
        .with_gamma(1.)\
        .with_constraint(AmplitudeConstraint.uniform(0.5))
    assert autd.send(g)

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 680)
        assert not np.all(phases == 0)


@pytest.mark.cuda
def test_evp_cuda():
    autd = Controller.builder()\
        .add_device(AUTD3.from_euler_zyz([0.0, 0.0, 0.0], [0.0, 0.0, 0.0]))\
        .open_with(Audit.builder())

    backend = CUDABackend()
    g = EVP(backend)\
        .add_focus(autd.geometry.center + np.array([30, 0, 150]), 0.5)\
        .add_foci_from_iter(map(lambda x: (autd.geometry.center + np.array([0, x, 150]), 0.5), [-30]))\
        .with_gamma(1.)\
        .with_constraint(AmplitudeConstraint.uniform(0.5))
    assert autd.send(g)

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 680)
        assert not np.all(phases == 0)