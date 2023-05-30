# This file is autogenerated
import threading
import ctypes
import os
from enum import IntEnum

class GainSTMMode(IntEnum):
    PhaseDutyFull = 0
    PhaseFull = 1
    PhaseHalf = 2

    @classmethod
    def from_param(cls, obj):
        return int(obj)


class TransMode(IntEnum):
    Legacy = 0
    Advanced = 1
    AdvancedPhase = 2

    @classmethod
    def from_param(cls, obj):
        return int(obj)


class Level(IntEnum):
    Critical = 0
    Error = 1
    Warn = 2
    Info = 3
    Debug = 4
    Trace = 5
    Off = 6

    @classmethod
    def from_param(cls, obj):
        return int(obj)


class TimerStrategy(IntEnum):
    Sleep = 0
    NativeTimer = 1
    BusyWait = 2

    @classmethod
    def from_param(cls, obj):
        return int(obj)


NUM_TRANS_IN_UNIT: int = 249
NUM_TRANS_IN_X: int = 18
NUM_TRANS_IN_Y: int = 14
TRANS_SPACING_MM: float = 10.16
DEVICE_HEIGHT_MM: float = 151.4
DEVICE_WIDTH_MM: float = 192.0
FPGA_CLK_FREQ: int = 163840000
FPGA_SUB_CLK_FREQ: int = 20480000
ERR: int = -1
TRUE: int = 1
FALSE: int = 0
