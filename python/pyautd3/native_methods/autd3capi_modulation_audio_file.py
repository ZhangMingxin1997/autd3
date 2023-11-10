# This file is autogenerated
import threading
import ctypes
import os
from .autd3capi_def import ModulationPtr, ResultModulation


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
            self.dll = ctypes.CDLL(os.path.join(bin_location, f'{bin_prefix}autd3capi_modulation_audio_file{bin_ext}'))
        except Exception:
            return

        self.dll.AUTDModulationWav.argtypes = [ctypes.c_char_p] 
        self.dll.AUTDModulationWav.restype = ResultModulation

        self.dll.AUTDModulationWavWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationWavWithSamplingFrequencyDivision.restype = ModulationPtr

        self.dll.AUTDModulationRawPCM.argtypes = [ctypes.c_char_p, ctypes.c_uint32] 
        self.dll.AUTDModulationRawPCM.restype = ResultModulation

        self.dll.AUTDModulationRawPCMWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationRawPCMWithSamplingFrequencyDivision.restype = ModulationPtr

    def modulation_wav(self, path: bytes) -> ResultModulation:
        return self.dll.AUTDModulationWav(path)

    def modulation_wav_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationWavWithSamplingFrequencyDivision(m, div)

    def modulation_raw_pcm(self, path: bytes, sample_rate: int) -> ResultModulation:
        return self.dll.AUTDModulationRawPCM(path, sample_rate)

    def modulation_raw_pcm_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationRawPCMWithSamplingFrequencyDivision(m, div)
