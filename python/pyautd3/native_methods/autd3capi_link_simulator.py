# This file is autogenerated
import threading
import ctypes
import os



class Singleton(type):
    _instances = {} # type: ignore
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
            self.dll = ctypes.CDLL(os.path.join(bin_location, f'{bin_prefix}autd3capi_link_simulator{bin_ext}'))
        except FileNotFoundError:
            return

        self.dll.AUTDLinkSimulator.argtypes = [ctypes.c_uint16] 
        self.dll.AUTDLinkSimulator.restype = ctypes.c_void_p

        self.dll.AUTDLinkSimulatorAddr.argtypes = [ctypes.c_void_p, ctypes.c_char_p] 
        self.dll.AUTDLinkSimulatorAddr.restype = ctypes.c_void_p

        self.dll.AUTDLinkSimulatorTimeout.argtypes = [ctypes.c_void_p, ctypes.c_uint64] 
        self.dll.AUTDLinkSimulatorTimeout.restype = ctypes.c_void_p

        self.dll.AUTDLinkSimulatorBuild.argtypes = [ctypes.c_void_p] 
        self.dll.AUTDLinkSimulatorBuild.restype = ctypes.c_void_p

    def link_simulator(self, port: int) -> ctypes.c_void_p:
        return self.dll.AUTDLinkSimulator(port)

    def link_simulator_addr(self, builder: ctypes.c_void_p, addr: bytes) -> ctypes.c_void_p:
        return self.dll.AUTDLinkSimulatorAddr(builder, addr)

    def link_simulator_timeout(self, builder: ctypes.c_void_p, timeout_ns: int) -> ctypes.c_void_p:
        return self.dll.AUTDLinkSimulatorTimeout(builder, timeout_ns)

    def link_simulator_build(self, builder: ctypes.c_void_p) -> ctypes.c_void_p:
        return self.dll.AUTDLinkSimulatorBuild(builder)
