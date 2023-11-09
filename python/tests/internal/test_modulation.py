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
import pytest

from pyautd3.modulation import Modulation, Sine
from tests.test_autd import create_controller


@pytest.mark.asyncio()
async def test_cache():
    autd = await create_controller()

    m = Sine(150).with_cache()

    assert await autd.send(m)

    for dev in autd.geometry:
        mod = autd.link.modulation(dev.idx)
        mod_expext = [
            85,
            107,
            132,
            157,
            183,
            210,
            236,
            245,
            219,
            192,
            166,
            140,
            115,
            92,
            70,
            50,
            33,
            19,
            8,
            2,
            0,
            2,
            8,
            19,
            33,
            50,
            70,
            92,
            115,
            140,
            166,
            192,
            219,
            245,
            236,
            210,
            183,
            157,
            132,
            107,
            85,
            63,
            44,
            28,
            15,
            6,
            0,
            0,
            3,
            11,
            23,
            39,
            57,
            77,
            100,
            123,
            148,
            174,
            201,
            227,
            255,
            227,
            201,
            174,
            148,
            123,
            100,
            77,
            57,
            39,
            23,
            11,
            3,
            0,
            0,
            6,
            15,
            28,
            44,
            63,
        ]
        assert np.array_equal(mod, mod_expext)
        assert autd.link.modulation_frequency_division(dev.idx) == 5120


class CacheTest(Modulation):
    calc_cnt: int

    def __init__(self: "CacheTest", freq_div: int = 5120) -> None:
        super().__init__(freq_div)
        self.calc_cnt = 0

    def calc(self: "CacheTest"):
        self.calc_cnt += 1
        return np.ones(2, dtype=np.float64)


@pytest.mark.asyncio()
async def test_cache_check_once():
    autd = await create_controller()

    m = CacheTest()
    assert await autd.send(m)
    assert m.calc_cnt == 1
    assert await autd.send(m)
    assert m.calc_cnt == 2

    m = CacheTest()
    m_cached = m.with_cache()

    assert await autd.send(m_cached)
    assert m.calc_cnt == 1
    assert await autd.send(m_cached)
    assert m.calc_cnt == 1


@pytest.mark.asyncio()
async def test_transform():
    autd = await create_controller()

    m = Sine(150).with_transform(lambda _i, v: v / 2)

    assert await autd.send(m)

    for dev in autd.geometry:
        mod = autd.link.modulation(dev.idx)
        mod_expext = [
            41,
            50,
            60,
            69,
            76,
            81,
            84,
            84,
            82,
            78,
            71,
            63,
            54,
            44,
            34,
            25,
            16,
            9,
            4,
            1,
            0,
            1,
            4,
            9,
            16,
            25,
            34,
            44,
            54,
            63,
            71,
            78,
            82,
            84,
            84,
            81,
            76,
            69,
            60,
            50,
            41,
            31,
            22,
            14,
            7,
            3,
            0,
            0,
            1,
            5,
            11,
            19,
            28,
            37,
            47,
            57,
            66,
            73,
            79,
            83,
            85,
            83,
            79,
            73,
            66,
            57,
            47,
            37,
            28,
            19,
            11,
            5,
            1,
            0,
            0,
            3,
            7,
            14,
            22,
            31,
        ]
        assert np.array_equal(mod, mod_expext)
        assert autd.link.modulation_frequency_division(dev.idx) == 5120


@pytest.mark.asyncio()
async def test_radiation_pressure():
    autd = await create_controller()

    m = Sine(150).with_radiation_pressure()

    assert await autd.send(m)

    for dev in autd.geometry:
        mod = autd.link.modulation(dev.idx)
        mod_expext = [
            127,
            146,
            165,
            184,
            204,
            223,
            242,
            248,
            229,
            210,
            191,
            172,
            153,
            133,
            114,
            95,
            76,
            57,
            38,
            19,
            0,
            19,
            38,
            57,
            76,
            95,
            114,
            133,
            153,
            172,
            191,
            210,
            229,
            248,
            242,
            223,
            204,
            184,
            165,
            146,
            127,
            108,
            89,
            70,
            51,
            31,
            12,
            6,
            25,
            44,
            63,
            82,
            101,
            121,
            140,
            159,
            178,
            197,
            216,
            235,
            255,
            235,
            216,
            197,
            178,
            159,
            140,
            121,
            102,
            82,
            63,
            44,
            25,
            6,
            12,
            31,
            50,
            70,
            89,
            108,
        ]
        assert np.array_equal(mod, mod_expext)
        assert autd.link.modulation_frequency_division(dev.idx) == 5120
