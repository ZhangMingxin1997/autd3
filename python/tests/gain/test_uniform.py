"""
File: test_uniform.py
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
import pytest

from pyautd3.gain import Uniform
from tests.test_autd import create_controller


@pytest.mark.asyncio()
async def test_uniform():
    autd = await create_controller()

    assert await autd.send_async(Uniform(0.5).with_phase(np.pi))

    for dev in autd.geometry:
        duties, phases = autd.link.duties_and_phases(dev.idx, 0)
        assert np.all(duties == 85)
        assert np.all(phases == 256)
