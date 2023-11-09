"""
File: runner.py
Project: samples
Created Date: 30/12/2020
Author: Shun Suzuki
-----
Last Modified: 25/10/2023
Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
-----
Copyright (c) 2020 Shun Suzuki. All rights reserved.

"""

from pyautd3 import Controller, Stop

from . import bessel, custom, flag, focus, group, holo, plane, stm, transtest, wav


async def run(autd: Controller) -> None:
    samples = [
        (focus.simple, "Single focus test"),
        (bessel.bessel, "Bessel beam test"),
        (plane.plane, "Plane wave test"),
        (wav.wav, "Wav modulation test"),
        (stm.stm_focus, "FocusSTM test"),
        (stm.stm_gain, "GainSTM test"),
        (holo.holo, "Multiple foci test"),
        (custom.custom, "Custom Gain & Modulation test"),
        (flag.flag, "Flag test"),
        (transtest.transtest, "TransducerTest test"),
    ]

    if autd.geometry.num_devices >= 2:
        samples.append((group.group, "Group test"))

    print("======== AUTD3 firmware information ========")
    print("\n".join([str(firm) for firm in await autd.firmware_info_list()]))
    print("============================================")

    while True:
        print("\n".join([f"[{i}]: {name}" for i, (_, name) in enumerate(samples)]))
        print("[Other]: finish")

        idx = input("choose number: ")
        idx = int(idx) if idx.isdigit() else None
        if idx is None or idx >= len(samples):
            break

        (fn, _) = samples[idx]
        await fn(autd)

        print("press enter to finish...")

        _ = input()

        print("finish.")
        await autd.send(Stop())

    await autd.close()
