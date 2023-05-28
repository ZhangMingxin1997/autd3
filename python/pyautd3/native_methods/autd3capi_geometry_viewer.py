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
            self.dll = ctypes.CDLL(os.path.join(bin_location, f'{bin_prefix}autd3capi-geometry-viewer{bin_ext}'))
        except FileNotFoundError:
            return

        self.dll.AUTDGeometryViewer.argtypes = [] 
        self.dll.AUTDGeometryViewer.restype = ctypes.c_void_p

        self.dll.AUTDGeometryViewerSize.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint32] 
        self.dll.AUTDGeometryViewerSize.restype = ctypes.c_void_p

        self.dll.AUTDGeometryViewerVsync.argtypes = [ctypes.c_void_p, ctypes.c_bool] 
        self.dll.AUTDGeometryViewerVsync.restype = ctypes.c_void_p

        self.dll.AUTDGeometryViewerRun.argtypes = [ctypes.c_void_p, ctypes.c_void_p] 
        self.dll.AUTDGeometryViewerRun.restype = ctypes.c_int32

    def geometry_viewer(self) -> ctypes.c_void_p:
        return self.dll.AUTDGeometryViewer()

    def geometry_viewer_size(self, viewer: ctypes.c_void_p, width: int, height: int) -> ctypes.c_void_p:
        return self.dll.AUTDGeometryViewerSize(viewer, width, height)

    def geometry_viewer_vsync(self, viewer: ctypes.c_void_p, vsync: bool) -> ctypes.c_void_p:
        return self.dll.AUTDGeometryViewerVsync(viewer, vsync)

    def geometry_viewer_run(self, viewer: ctypes.c_void_p, cnt: ctypes.c_void_p) -> ctypes.c_int32:
        return self.dll.AUTDGeometryViewerRun(viewer, cnt)
