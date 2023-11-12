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


class TimerStrategy(IntEnum):
    Sleep = 0
    BusyWait = 1
    NativeTimer = 2

    @classmethod
    def from_param(cls, obj):
        return int(obj)


class ControllerPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class GeometryPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class DevicePtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class TransducerPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class LinkBuilderPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class LinkPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class DatagramPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class DatagramSpecialPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class GainPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class ModulationPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class STMPropsPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class BackendPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class ConstraintPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class GroupGainMapPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class ResultI32(ctypes.Structure):
    _fields_ = [("result", ctypes.c_int32), ("err_len", ctypes.c_uint32), ("err", ctypes.c_void_p)]


class ResultController(ctypes.Structure):
    _fields_ = [("result", ControllerPtr), ("err_len", ctypes.c_uint32), ("err", ctypes.c_void_p)]


class ResultGainCalcDrivesMap(ctypes.Structure):
    _fields_ = [("result", ctypes.c_void_p), ("err_len", ctypes.c_uint32), ("err", ctypes.c_void_p)]


class ResultModulation(ctypes.Structure):
    _fields_ = [("result", ModulationPtr), ("err_len", ctypes.c_uint32), ("err", ctypes.c_void_p)]


class ResultBackend(ctypes.Structure):
    _fields_ = [("result", BackendPtr), ("err_len", ctypes.c_uint32), ("err", ctypes.c_void_p)]


DEFAULT_CORRECTED_ALPHA: float = 0.803
NUM_TRANS_IN_UNIT: int = 249
NUM_TRANS_IN_X: int = 18
NUM_TRANS_IN_Y: int = 14
TRANS_SPACING_MM: float = 10.16
DEVICE_HEIGHT_MM: float = 151.4
DEVICE_WIDTH_MM: float = 192.0
FPGA_CLK_FREQ: int = 20480000
ULTRASOUND_FREQUENCY: float = 40000.0
AUTD3_ERR: int = -1
AUTD3_TRUE: int = 1
AUTD3_FALSE: int = 0

class Singleton(type):
    _instances = {}  # type: ignore
    _lock = threading.Lock()

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            with cls._lock:
                if cls not in cls._instances:
                    cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]


class NativeMethods(metaclass=Singleton):

    def init_dll(self, bin_location: str, bin_prefix: str, bin_ext: str):
        try:
            self.dll = ctypes.CDLL(os.path.join(bin_location, f'{bin_prefix}autd3capi_def{bin_ext}'))
        except Exception:
            return

        self.dll.AUTDEmitIntensityNormalizedFrom.argtypes = [ctypes.c_uint16] 
        self.dll.AUTDEmitIntensityNormalizedFrom.restype = ctypes.c_double

        self.dll.AUTDEmitIntensityDutyRatioFrom.argtypes = [ctypes.c_uint16] 
        self.dll.AUTDEmitIntensityDutyRatioFrom.restype = ctypes.c_double

        self.dll.AUTDEmitIntensityNormalizedInto.argtypes = [ctypes.c_double] 
        self.dll.AUTDEmitIntensityNormalizedInto.restype = ResultI32

        self.dll.AUTDEmitIntensityNormalizedCorrectedInto.argtypes = [ctypes.c_double, ctypes.c_double] 
        self.dll.AUTDEmitIntensityNormalizedCorrectedInto.restype = ResultI32

        self.dll.AUTDEmitIntensityDutyRatioInto.argtypes = [ctypes.c_double] 
        self.dll.AUTDEmitIntensityDutyRatioInto.restype = ResultI32

        self.dll.AUTDEmitIntensityPulseWidthInto.argtypes = [ctypes.c_uint16] 
        self.dll.AUTDEmitIntensityPulseWidthInto.restype = ResultI32

        self.dll.AUTDGetErr.argtypes = [ctypes.c_void_p, ctypes.c_char_p] 
        self.dll.AUTDGetErr.restype = None

    def emit_intensity_normalized_from(self, pulse_width: int) -> ctypes.c_double:
        return self.dll.AUTDEmitIntensityNormalizedFrom(pulse_width)

    def emit_intensity_duty_ratio_from(self, pulse_width: int) -> ctypes.c_double:
        return self.dll.AUTDEmitIntensityDutyRatioFrom(pulse_width)

    def emit_intensity_normalized_into(self, value: float) -> ResultI32:
        return self.dll.AUTDEmitIntensityNormalizedInto(value)

    def emit_intensity_normalized_corrected_into(self, value: float, alpha: float) -> ResultI32:
        return self.dll.AUTDEmitIntensityNormalizedCorrectedInto(value, alpha)

    def emit_intensity_duty_ratio_into(self, value: float) -> ResultI32:
        return self.dll.AUTDEmitIntensityDutyRatioInto(value)

    def emit_intensity_pulse_width_into(self, value: int) -> ResultI32:
        return self.dll.AUTDEmitIntensityPulseWidthInto(value)

    def get_err(self, src: ctypes.c_void_p | None, dst: ctypes.Array[ctypes.c_char] | None) -> None:
        return self.dll.AUTDGetErr(src, dst)
