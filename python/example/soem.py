"""
File: soem.py
Project: example
Created Date: 30/12/2020
Author: Shun Suzuki
-----
Last Modified: 11/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2020 Shun Suzuki. All rights reserved.

"""

import ctypes
import os

from samples import runner

from pyautd3 import AUTD3, Controller
from pyautd3.link.soem import SOEM, OnErrFunc


def on_lost(msg: ctypes.c_char_p):
    print(msg.decode("utf-8"), end="")
    os._exit(-1)


if __name__ == "__main__":
    on_lost_func = OnErrFunc(on_lost)
    autd = (
        Controller.builder().add_device(AUTD3.from_euler_zyz([0.0, 0.0, 0.0], [0.0, 0.0, 0.0])).open_with(SOEM.builder().with_on_lost(on_lost_func))
    )

    runner.run(autd)
