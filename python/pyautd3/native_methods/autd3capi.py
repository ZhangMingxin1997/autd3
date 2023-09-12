# This file is autogenerated
import threading
import ctypes
import os
from .autd3capi_def import ControllerPtr, DatagramPtr, DatagramSpecialPtr, DevicePtr, GainPtr, GainSTMMode, GeometryPtr, GroupGainMapPtr, Level, LinkPtr, ModulationPtr, STMPropsPtr, TransMode


class ControllerBuilderPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class FirmwareInfoListPtr(ctypes.Structure):
    _fields_ = [("_0", ctypes.c_void_p)]


class Drive(ctypes.Structure):
    _fields_ = [("phase", ctypes.c_double), ("amp", ctypes.c_double)]


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
            self.dll = ctypes.CDLL(os.path.join(bin_location, f'{bin_prefix}autd3capi{bin_ext}'))
        except Exception:
            return

        self.dll.AUTDGainBessel.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double] 
        self.dll.AUTDGainBessel.restype = GainPtr

        self.dll.AUTDGainBesselWithAmp.argtypes = [GainPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGainBesselWithAmp.restype = GainPtr

        self.dll.AUTDGainCustom.argtypes = [] 
        self.dll.AUTDGainCustom.restype = GainPtr

        self.dll.AUTDGainCustomSet.argtypes = [GainPtr, ctypes.c_uint32, ctypes.POINTER(Drive), ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGainCustomSet.restype = GainPtr

        self.dll.AUTDGainFocus.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double] 
        self.dll.AUTDGainFocus.restype = GainPtr

        self.dll.AUTDGainFocusWithAmp.argtypes = [GainPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGainFocusWithAmp.restype = GainPtr

        self.dll.AUTDGainGroupCreateMap.argtypes = [ctypes.POINTER(ctypes.c_uint32), ctypes.c_uint32] 
        self.dll.AUTDGainGroupCreateMap.restype = GroupGainMapPtr

        self.dll.AUTDGainGroupMapSet.argtypes = [GroupGainMapPtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_int32)]  # type: ignore 
        self.dll.AUTDGainGroupMapSet.restype = GroupGainMapPtr

        self.dll.AUTDGainGroup.argtypes = [GroupGainMapPtr, ctypes.POINTER(ctypes.c_int32), ctypes.POINTER(GainPtr), ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGainGroup.restype = GainPtr

        self.dll.AUTDGainIntoDatagram.argtypes = [GainPtr]  # type: ignore 
        self.dll.AUTDGainIntoDatagram.restype = DatagramPtr

        self.dll.AUTDGainCalc.argtypes = [GainPtr, GeometryPtr, ctypes.POINTER(ctypes.POINTER(Drive)), ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDGainCalc.restype = ctypes.c_int32

        self.dll.AUTDGainNull.argtypes = [] 
        self.dll.AUTDGainNull.restype = GainPtr

        self.dll.AUTDGainPlane.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double] 
        self.dll.AUTDGainPlane.restype = GainPtr

        self.dll.AUTDGainPlaneWithAmp.argtypes = [GainPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGainPlaneWithAmp.restype = GainPtr

        self.dll.AUTDGainTransducerTest.argtypes = [] 
        self.dll.AUTDGainTransducerTest.restype = GainPtr

        self.dll.AUTDGainTransducerTestSet.argtypes = [GainPtr, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGainTransducerTestSet.restype = GainPtr

        self.dll.AUTDGainUniform.argtypes = [ctypes.c_double] 
        self.dll.AUTDGainUniform.restype = GainPtr

        self.dll.AUTDGainUniformWithPhase.argtypes = [GainPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGainUniformWithPhase.restype = GainPtr

        self.dll.AUTDGetDevice.argtypes = [GeometryPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGetDevice.restype = DevicePtr

        self.dll.AUTDDeviceNumTransducers.argtypes = [DevicePtr]  # type: ignore 
        self.dll.AUTDDeviceNumTransducers.restype = ctypes.c_uint32

        self.dll.AUTDDeviceGetSoundSpeed.argtypes = [DevicePtr]  # type: ignore 
        self.dll.AUTDDeviceGetSoundSpeed.restype = ctypes.c_double

        self.dll.AUTDDeviceSetSoundSpeed.argtypes = [DevicePtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceSetSoundSpeed.restype = None

        self.dll.AUTDDeviceSetSoundSpeedFromTemp.argtypes = [DevicePtr, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceSetSoundSpeedFromTemp.restype = None

        self.dll.AUTDDeviceGetAttenuation.argtypes = [DevicePtr]  # type: ignore 
        self.dll.AUTDDeviceGetAttenuation.restype = ctypes.c_double

        self.dll.AUTDDeviceSetAttenuation.argtypes = [DevicePtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceSetAttenuation.restype = None

        self.dll.AUTDDeviceCenter.argtypes = [DevicePtr, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDDeviceCenter.restype = None

        self.dll.AUTDDeviceTranslate.argtypes = [DevicePtr, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceTranslate.restype = None

        self.dll.AUTDDeviceRotate.argtypes = [DevicePtr, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceRotate.restype = None

        self.dll.AUTDDeviceAffine.argtypes = [DevicePtr, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDDeviceAffine.restype = None

        self.dll.AUTDDeviceSetReadsFPGAInfo.argtypes = [DevicePtr, ctypes.c_bool]  # type: ignore 
        self.dll.AUTDDeviceSetReadsFPGAInfo.restype = None

        self.dll.AUTDDeviceSetForceFan.argtypes = [DevicePtr, ctypes.c_bool]  # type: ignore 
        self.dll.AUTDDeviceSetForceFan.restype = None

        self.dll.AUTDGetGeometry.argtypes = [ControllerPtr]  # type: ignore 
        self.dll.AUTDGetGeometry.restype = GeometryPtr

        self.dll.AUTDGeometryNumDevices.argtypes = [GeometryPtr]  # type: ignore 
        self.dll.AUTDGeometryNumDevices.restype = ctypes.c_uint32

        self.dll.AUTDTransPosition.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDTransPosition.restype = None

        self.dll.AUTDTransRotation.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDTransRotation.restype = None

        self.dll.AUTDTransXDirection.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDTransXDirection.restype = None

        self.dll.AUTDTransYDirection.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDTransYDirection.restype = None

        self.dll.AUTDTransZDirection.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.POINTER(ctypes.c_double)]  # type: ignore 
        self.dll.AUTDTransZDirection.restype = None

        self.dll.AUTDGetTransFrequency.argtypes = [DevicePtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGetTransFrequency.restype = ctypes.c_double

        self.dll.AUTDSetTransFrequency.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDSetTransFrequency.restype = ctypes.c_bool

        self.dll.AUTDGetTransCycle.argtypes = [DevicePtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGetTransCycle.restype = ctypes.c_uint16

        self.dll.AUTDSetTransCycle.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_uint16, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDSetTransCycle.restype = ctypes.c_bool

        self.dll.AUTDGetWavelength.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_double]  # type: ignore 
        self.dll.AUTDGetWavelength.restype = ctypes.c_double

        self.dll.AUTDGetTransModDelay.argtypes = [DevicePtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDGetTransModDelay.restype = ctypes.c_uint16

        self.dll.AUTDSetTransModDelay.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_uint16]  # type: ignore 
        self.dll.AUTDSetTransModDelay.restype = None

        self.dll.AUTDTransTranslate.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDTransTranslate.restype = None

        self.dll.AUTDTransRotate.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDTransRotate.restype = None

        self.dll.AUTDTransAffine.argtypes = [DevicePtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDTransAffine.restype = None

        self.dll.AUTDCreateControllerBuilder.argtypes = [] 
        self.dll.AUTDCreateControllerBuilder.restype = ControllerBuilderPtr

        self.dll.AUTDAddDevice.argtypes = [ControllerBuilderPtr, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDAddDevice.restype = ControllerBuilderPtr

        self.dll.AUTDAddDeviceQuaternion.argtypes = [ControllerBuilderPtr, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDAddDeviceQuaternion.restype = ControllerBuilderPtr

        self.dll.AUTDControllerOpenWith.argtypes = [ControllerBuilderPtr, LinkPtr, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDControllerOpenWith.restype = ControllerPtr

        self.dll.AUTDClose.argtypes = [ControllerPtr, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDClose.restype = ctypes.c_bool

        self.dll.AUTDFreeController.argtypes = [ControllerPtr]  # type: ignore 
        self.dll.AUTDFreeController.restype = None

        self.dll.AUTDGetFPGAInfo.argtypes = [ControllerPtr, ctypes.POINTER(ctypes.c_uint8), ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDGetFPGAInfo.restype = ctypes.c_bool

        self.dll.AUTDGetFirmwareInfoListPointer.argtypes = [ControllerPtr, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDGetFirmwareInfoListPointer.restype = FirmwareInfoListPtr

        self.dll.AUTDGetFirmwareInfo.argtypes = [FirmwareInfoListPtr, ctypes.c_uint32, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDGetFirmwareInfo.restype = None

        self.dll.AUTDFreeFirmwareInfoListPointer.argtypes = [FirmwareInfoListPtr]  # type: ignore 
        self.dll.AUTDFreeFirmwareInfoListPointer.restype = None

        self.dll.AUTDGetLatestFirmware.argtypes = [ctypes.c_char_p] 
        self.dll.AUTDGetLatestFirmware.restype = None

        self.dll.AUTDSynchronize.argtypes = [] 
        self.dll.AUTDSynchronize.restype = DatagramPtr

        self.dll.AUTDClear.argtypes = [] 
        self.dll.AUTDClear.restype = DatagramPtr

        self.dll.AUTDUpdateFlags.argtypes = [] 
        self.dll.AUTDUpdateFlags.restype = DatagramPtr

        self.dll.AUTDStop.argtypes = [] 
        self.dll.AUTDStop.restype = DatagramSpecialPtr

        self.dll.AUTDModDelayConfig.argtypes = [] 
        self.dll.AUTDModDelayConfig.restype = DatagramPtr

        self.dll.AUTDCreateSilencer.argtypes = [ctypes.c_uint16] 
        self.dll.AUTDCreateSilencer.restype = DatagramPtr

        self.dll.AUTDCreateAmplitudes.argtypes = [ctypes.c_double] 
        self.dll.AUTDCreateAmplitudes.restype = DatagramPtr

        self.dll.AUTDSend.argtypes = [ControllerPtr, TransMode, DatagramPtr, DatagramPtr, ctypes.c_int64, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDSend.restype = ctypes.c_int32

        self.dll.AUTDSendSpecial.argtypes = [ControllerPtr, TransMode, DatagramSpecialPtr, ctypes.c_int64, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDSendSpecial.restype = ctypes.c_int32

        self.dll.AUTDLinkBundle.argtypes = [LinkPtr, LinkPtr]  # type: ignore 
        self.dll.AUTDLinkBundle.restype = LinkPtr

        self.dll.AUTDLinkDebug.argtypes = [] 
        self.dll.AUTDLinkDebug.restype = LinkPtr

        self.dll.AUTDLinkDebugWithLogLevel.argtypes = [LinkPtr, Level]  # type: ignore 
        self.dll.AUTDLinkDebugWithLogLevel.restype = LinkPtr

        self.dll.AUTDLinkDebugWithLogFunc.argtypes = [LinkPtr, ctypes.c_void_p, ctypes.c_void_p]  # type: ignore 
        self.dll.AUTDLinkDebugWithLogFunc.restype = LinkPtr

        self.dll.AUTDLinkDebugWithTimeout.argtypes = [LinkPtr, ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDLinkDebugWithTimeout.restype = LinkPtr

        self.dll.AUTDLinkLog.argtypes = [LinkPtr]  # type: ignore 
        self.dll.AUTDLinkLog.restype = LinkPtr

        self.dll.AUTDLinkLogWithLogLevel.argtypes = [LinkPtr, Level]  # type: ignore 
        self.dll.AUTDLinkLogWithLogLevel.restype = LinkPtr

        self.dll.AUTDLinkLogWithLogFunc.argtypes = [LinkPtr, ctypes.c_void_p, ctypes.c_void_p]  # type: ignore 
        self.dll.AUTDLinkLogWithLogFunc.restype = LinkPtr

        self.dll.AUTDModulationCustom.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_double), ctypes.c_uint64] 
        self.dll.AUTDModulationCustom.restype = ModulationPtr

        self.dll.AUTDModulationWithLowPass.argtypes = [ModulationPtr, ctypes.c_uint32, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationWithLowPass.restype = ModulationPtr

        self.dll.AUTDModulationWithHighPass.argtypes = [ModulationPtr, ctypes.c_uint32, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationWithHighPass.restype = ModulationPtr

        self.dll.AUTDModulationWithBandPass.argtypes = [ModulationPtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationWithBandPass.restype = ModulationPtr

        self.dll.AUTDModulationWithBandStop.argtypes = [ModulationPtr, ctypes.c_uint32, ctypes.c_double, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationWithBandStop.restype = ModulationPtr

        self.dll.AUTDModulationFourier.argtypes = [] 
        self.dll.AUTDModulationFourier.restype = ModulationPtr

        self.dll.AUTDModulationFourierAddComponent.argtypes = [ModulationPtr, ModulationPtr]  # type: ignore 
        self.dll.AUTDModulationFourierAddComponent.restype = ModulationPtr

        self.dll.AUTDModulationSamplingFrequencyDivision.argtypes = [ModulationPtr]  # type: ignore 
        self.dll.AUTDModulationSamplingFrequencyDivision.restype = ctypes.c_uint32

        self.dll.AUTDModulationIntoDatagram.argtypes = [ModulationPtr]  # type: ignore 
        self.dll.AUTDModulationIntoDatagram.restype = DatagramPtr

        self.dll.AUTDModulationSize.argtypes = [ModulationPtr, ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDModulationSize.restype = ctypes.c_int32

        self.dll.AUTDModulationCalc.argtypes = [ModulationPtr, ctypes.POINTER(ctypes.c_double), ctypes.c_char_p]  # type: ignore 
        self.dll.AUTDModulationCalc.restype = ctypes.c_int32

        self.dll.AUTDModulationSine.argtypes = [ctypes.c_uint32] 
        self.dll.AUTDModulationSine.restype = ModulationPtr

        self.dll.AUTDModulationSineWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationSineWithSamplingFrequencyDivision.restype = ModulationPtr

        self.dll.AUTDModulationSineWithAmp.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSineWithAmp.restype = ModulationPtr

        self.dll.AUTDModulationSineWithPhase.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSineWithPhase.restype = ModulationPtr

        self.dll.AUTDModulationSineWithOffset.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSineWithOffset.restype = ModulationPtr

        self.dll.AUTDModulationSineLegacy.argtypes = [ctypes.c_double] 
        self.dll.AUTDModulationSineLegacy.restype = ModulationPtr

        self.dll.AUTDModulationSineLegacyWithAmp.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSineLegacyWithAmp.restype = ModulationPtr

        self.dll.AUTDModulationSineLegacyWithOffset.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSineLegacyWithOffset.restype = ModulationPtr

        self.dll.AUTDModulationSineLegacyWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationSineLegacyWithSamplingFrequencyDivision.restype = ModulationPtr

        self.dll.AUTDModulationSquare.argtypes = [ctypes.c_uint32] 
        self.dll.AUTDModulationSquare.restype = ModulationPtr

        self.dll.AUTDModulationSquareWithLow.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSquareWithLow.restype = ModulationPtr

        self.dll.AUTDModulationSquareWithHigh.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSquareWithHigh.restype = ModulationPtr

        self.dll.AUTDModulationSquareWithDuty.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationSquareWithDuty.restype = ModulationPtr

        self.dll.AUTDModulationSquareWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationSquareWithSamplingFrequencyDivision.restype = ModulationPtr

        self.dll.AUTDModulationStatic.argtypes = [] 
        self.dll.AUTDModulationStatic.restype = ModulationPtr

        self.dll.AUTDModulationStaticWithAmp.argtypes = [ModulationPtr, ctypes.c_double]  # type: ignore 
        self.dll.AUTDModulationStaticWithAmp.restype = ModulationPtr

        self.dll.AUTDModulationStaticWithSamplingFrequencyDivision.argtypes = [ModulationPtr, ctypes.c_uint32]  # type: ignore 
        self.dll.AUTDModulationStaticWithSamplingFrequencyDivision.restype = ModulationPtr

        self.dll.AUTDFocusSTM.argtypes = [STMPropsPtr, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_uint8), ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDFocusSTM.restype = DatagramPtr

        self.dll.AUTDGainSTM.argtypes = [STMPropsPtr, ctypes.POINTER(GainPtr), ctypes.c_uint32, GainSTMMode]  # type: ignore 
        self.dll.AUTDGainSTM.restype = DatagramPtr

        self.dll.AUTDGainSTMAddGain.argtypes = [DatagramPtr, GainPtr]  # type: ignore 
        self.dll.AUTDGainSTMAddGain.restype = DatagramPtr

        self.dll.AUTDSTMProps.argtypes = [ctypes.c_double] 
        self.dll.AUTDSTMProps.restype = STMPropsPtr

        self.dll.AUTDSTMPropsWithSamplingFreq.argtypes = [ctypes.c_double] 
        self.dll.AUTDSTMPropsWithSamplingFreq.restype = STMPropsPtr

        self.dll.AUTDSTMPropsWithSamplingFreqDiv.argtypes = [ctypes.c_uint32] 
        self.dll.AUTDSTMPropsWithSamplingFreqDiv.restype = STMPropsPtr

        self.dll.AUTDSTMPropsWithSamplingPeriod.argtypes = [ctypes.c_uint64] 
        self.dll.AUTDSTMPropsWithSamplingPeriod.restype = STMPropsPtr

        self.dll.AUTDSTMPropsWithStartIdx.argtypes = [STMPropsPtr, ctypes.c_int32]  # type: ignore 
        self.dll.AUTDSTMPropsWithStartIdx.restype = STMPropsPtr

        self.dll.AUTDSTMPropsWithFinishIdx.argtypes = [STMPropsPtr, ctypes.c_int32]  # type: ignore 
        self.dll.AUTDSTMPropsWithFinishIdx.restype = STMPropsPtr

        self.dll.AUTDSTMPropsFrequency.argtypes = [STMPropsPtr, ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDSTMPropsFrequency.restype = ctypes.c_double

        self.dll.AUTDSTMPropsSamplingFrequency.argtypes = [STMPropsPtr, ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDSTMPropsSamplingFrequency.restype = ctypes.c_double

        self.dll.AUTDSTMPropsSamplingFrequencyDivision.argtypes = [STMPropsPtr, ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDSTMPropsSamplingFrequencyDivision.restype = ctypes.c_uint32

        self.dll.AUTDSTMPropsSamplingPeriod.argtypes = [STMPropsPtr, ctypes.c_uint64]  # type: ignore 
        self.dll.AUTDSTMPropsSamplingPeriod.restype = ctypes.c_uint64

        self.dll.AUTDSTMPropsStartIdx.argtypes = [STMPropsPtr]  # type: ignore 
        self.dll.AUTDSTMPropsStartIdx.restype = ctypes.c_int32

        self.dll.AUTDSTMPropsFinishIdx.argtypes = [STMPropsPtr]  # type: ignore 
        self.dll.AUTDSTMPropsFinishIdx.restype = ctypes.c_int32

    def gain_bessel(self, x: float, y: float, z: float, nx: float, ny: float, nz: float, theta_z: float) -> GainPtr:
        return self.dll.AUTDGainBessel(x, y, z, nx, ny, nz, theta_z)

    def gain_bessel_with_amp(self, bessel: GainPtr, amp: float) -> GainPtr:
        return self.dll.AUTDGainBesselWithAmp(bessel, amp)

    def gain_custom(self) -> GainPtr:
        return self.dll.AUTDGainCustom()

    def gain_custom_set(self, custom: GainPtr, dev_idx: int, ptr: ctypes.Array, len: int) -> GainPtr:
        return self.dll.AUTDGainCustomSet(custom, dev_idx, ptr, len)

    def gain_focus(self, x: float, y: float, z: float) -> GainPtr:
        return self.dll.AUTDGainFocus(x, y, z)

    def gain_focus_with_amp(self, focus: GainPtr, amp: float) -> GainPtr:
        return self.dll.AUTDGainFocusWithAmp(focus, amp)

    def gain_group_create_map(self, device_indices_ptr: ctypes.Array[ctypes.c_uint32], num_devices: int) -> GroupGainMapPtr:
        return self.dll.AUTDGainGroupCreateMap(device_indices_ptr, num_devices)

    def gain_group_map_set(self, map: GroupGainMapPtr, dev_idx: int, map_data: ctypes.Array[ctypes.c_int32]) -> GroupGainMapPtr:
        return self.dll.AUTDGainGroupMapSet(map, dev_idx, map_data)

    def gain_group(self, map: GroupGainMapPtr, keys_ptr: ctypes.Array[ctypes.c_int32], values_ptr: ctypes.Array, kv_len: int) -> GainPtr:
        return self.dll.AUTDGainGroup(map, keys_ptr, values_ptr, kv_len)

    def gain_into_datagram(self, gain: GainPtr) -> DatagramPtr:
        return self.dll.AUTDGainIntoDatagram(gain)

    def gain_calc(self, gain: GainPtr, geometry: GeometryPtr, drives: ctypes.Array, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_int32:
        return self.dll.AUTDGainCalc(gain, geometry, drives, err)

    def gain_null(self) -> GainPtr:
        return self.dll.AUTDGainNull()

    def gain_plane(self, nx: float, ny: float, nz: float) -> GainPtr:
        return self.dll.AUTDGainPlane(nx, ny, nz)

    def gain_plane_with_amp(self, plane: GainPtr, amp: float) -> GainPtr:
        return self.dll.AUTDGainPlaneWithAmp(plane, amp)

    def gain_transducer_test(self) -> GainPtr:
        return self.dll.AUTDGainTransducerTest()

    def gain_transducer_test_set(self, trans_test: GainPtr, dev_idx: int, tr_idx: int, phase: float, amp: float) -> GainPtr:
        return self.dll.AUTDGainTransducerTestSet(trans_test, dev_idx, tr_idx, phase, amp)

    def gain_uniform(self, amp: float) -> GainPtr:
        return self.dll.AUTDGainUniform(amp)

    def gain_uniform_with_phase(self, uniform: GainPtr, phase: float) -> GainPtr:
        return self.dll.AUTDGainUniformWithPhase(uniform, phase)

    def get_device(self, geo: GeometryPtr, dev_idx: int) -> DevicePtr:
        return self.dll.AUTDGetDevice(geo, dev_idx)

    def device_num_transducers(self, dev: DevicePtr) -> ctypes.c_uint32:
        return self.dll.AUTDDeviceNumTransducers(dev)

    def device_get_sound_speed(self, dev: DevicePtr) -> ctypes.c_double:
        return self.dll.AUTDDeviceGetSoundSpeed(dev)

    def device_set_sound_speed(self, dev: DevicePtr, value: float) -> None:
        return self.dll.AUTDDeviceSetSoundSpeed(dev, value)

    def device_set_sound_speed_from_temp(self, dev: DevicePtr, temp: float, k: float, r: float, m: float) -> None:
        return self.dll.AUTDDeviceSetSoundSpeedFromTemp(dev, temp, k, r, m)

    def device_get_attenuation(self, dev: DevicePtr) -> ctypes.c_double:
        return self.dll.AUTDDeviceGetAttenuation(dev)

    def device_set_attenuation(self, dev: DevicePtr, value: float) -> None:
        return self.dll.AUTDDeviceSetAttenuation(dev, value)

    def device_center(self, dev: DevicePtr, center: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDDeviceCenter(dev, center)

    def device_translate(self, dev: DevicePtr, x: float, y: float, z: float) -> None:
        return self.dll.AUTDDeviceTranslate(dev, x, y, z)

    def device_rotate(self, dev: DevicePtr, w: float, i: float, j: float, k: float) -> None:
        return self.dll.AUTDDeviceRotate(dev, w, i, j, k)

    def device_affine(self, dev: DevicePtr, x: float, y: float, z: float, w: float, i: float, j: float, k: float) -> None:
        return self.dll.AUTDDeviceAffine(dev, x, y, z, w, i, j, k)

    def device_set_reads_fpga_info(self, dev: DevicePtr, value: bool) -> None:
        return self.dll.AUTDDeviceSetReadsFPGAInfo(dev, value)

    def device_set_force_fan(self, dev: DevicePtr, value: bool) -> None:
        return self.dll.AUTDDeviceSetForceFan(dev, value)

    def get_geometry(self, cnt: ControllerPtr) -> GeometryPtr:
        return self.dll.AUTDGetGeometry(cnt)

    def geometry_num_devices(self, geo: GeometryPtr) -> ctypes.c_uint32:
        return self.dll.AUTDGeometryNumDevices(geo)

    def trans_position(self, dev: DevicePtr, tr_idx: int, pos: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDTransPosition(dev, tr_idx, pos)

    def trans_rotation(self, dev: DevicePtr, tr_idx: int, rot: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDTransRotation(dev, tr_idx, rot)

    def trans_x_direction(self, dev: DevicePtr, tr_idx: int, dir: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDTransXDirection(dev, tr_idx, dir)

    def trans_y_direction(self, dev: DevicePtr, tr_idx: int, dir: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDTransYDirection(dev, tr_idx, dir)

    def trans_z_direction(self, dev: DevicePtr, tr_idx: int, dir: ctypes.Array[ctypes.c_double]) -> None:
        return self.dll.AUTDTransZDirection(dev, tr_idx, dir)

    def get_trans_frequency(self, dev: DevicePtr, idx: int) -> ctypes.c_double:
        return self.dll.AUTDGetTransFrequency(dev, idx)

    def set_trans_frequency(self, dev: DevicePtr, idx: int, value: float, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_bool:
        return self.dll.AUTDSetTransFrequency(dev, idx, value, err)

    def get_trans_cycle(self, dev: DevicePtr, idx: int) -> ctypes.c_uint16:
        return self.dll.AUTDGetTransCycle(dev, idx)

    def set_trans_cycle(self, dev: DevicePtr, idx: int, value: int, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_bool:
        return self.dll.AUTDSetTransCycle(dev, idx, value, err)

    def get_wavelength(self, dev: DevicePtr, idx: int, sound_speed: float) -> ctypes.c_double:
        return self.dll.AUTDGetWavelength(dev, idx, sound_speed)

    def get_trans_mod_delay(self, dev: DevicePtr, tr_idx: int) -> ctypes.c_uint16:
        return self.dll.AUTDGetTransModDelay(dev, tr_idx)

    def set_trans_mod_delay(self, dev: DevicePtr, tr_idx: int, delay: int) -> None:
        return self.dll.AUTDSetTransModDelay(dev, tr_idx, delay)

    def trans_translate(self, dev: DevicePtr, tr_idx: int, x: float, y: float, z: float) -> None:
        return self.dll.AUTDTransTranslate(dev, tr_idx, x, y, z)

    def trans_rotate(self, dev: DevicePtr, tr_idx: int, w: float, i: float, j: float, k: float) -> None:
        return self.dll.AUTDTransRotate(dev, tr_idx, w, i, j, k)

    def trans_affine(self, dev: DevicePtr, tr_idx: int, x: float, y: float, z: float, w: float, i: float, j: float, k: float) -> None:
        return self.dll.AUTDTransAffine(dev, tr_idx, x, y, z, w, i, j, k)

    def create_controller_builder(self) -> ControllerBuilderPtr:
        return self.dll.AUTDCreateControllerBuilder()

    def add_device(self, builder: ControllerBuilderPtr, x: float, y: float, z: float, rz1: float, ry: float, rz2: float) -> ControllerBuilderPtr:
        return self.dll.AUTDAddDevice(builder, x, y, z, rz1, ry, rz2)

    def add_device_quaternion(self, builder: ControllerBuilderPtr, x: float, y: float, z: float, qw: float, qx: float, qy: float, qz: float) -> ControllerBuilderPtr:
        return self.dll.AUTDAddDeviceQuaternion(builder, x, y, z, qw, qx, qy, qz)

    def controller_open_with(self, builder: ControllerBuilderPtr, link: LinkPtr, err: ctypes.Array[ctypes.c_char]) -> ControllerPtr:
        return self.dll.AUTDControllerOpenWith(builder, link, err)

    def close(self, cnt: ControllerPtr, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_bool:
        return self.dll.AUTDClose(cnt, err)

    def free_controller(self, cnt: ControllerPtr) -> None:
        return self.dll.AUTDFreeController(cnt)

    def get_fpga_info(self, cnt: ControllerPtr, out: ctypes.Array[ctypes.c_uint8], err: ctypes.Array[ctypes.c_char]) -> ctypes.c_bool:
        return self.dll.AUTDGetFPGAInfo(cnt, out, err)

    def get_firmware_info_list_pointer(self, cnt: ControllerPtr, err: ctypes.Array[ctypes.c_char]) -> FirmwareInfoListPtr:
        return self.dll.AUTDGetFirmwareInfoListPointer(cnt, err)

    def get_firmware_info(self, p_info_list: FirmwareInfoListPtr, idx: int, info: ctypes.Array[ctypes.c_char]) -> None:
        return self.dll.AUTDGetFirmwareInfo(p_info_list, idx, info)

    def free_firmware_info_list_pointer(self, p_info_list: FirmwareInfoListPtr) -> None:
        return self.dll.AUTDFreeFirmwareInfoListPointer(p_info_list)

    def get_latest_firmware(self, latest: ctypes.Array[ctypes.c_char]) -> None:
        return self.dll.AUTDGetLatestFirmware(latest)

    def synchronize(self) -> DatagramPtr:
        return self.dll.AUTDSynchronize()

    def clear(self) -> DatagramPtr:
        return self.dll.AUTDClear()

    def update_flags(self) -> DatagramPtr:
        return self.dll.AUTDUpdateFlags()

    def stop(self) -> DatagramSpecialPtr:
        return self.dll.AUTDStop()

    def mod_delay_config(self) -> DatagramPtr:
        return self.dll.AUTDModDelayConfig()

    def create_silencer(self, step: int) -> DatagramPtr:
        return self.dll.AUTDCreateSilencer(step)

    def create_amplitudes(self, amp: float) -> DatagramPtr:
        return self.dll.AUTDCreateAmplitudes(amp)

    def send(self, cnt: ControllerPtr, mode: TransMode, d1: DatagramPtr, d2: DatagramPtr, timeout_ns: int, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_int32:
        return self.dll.AUTDSend(cnt, mode, d1, d2, timeout_ns, err)

    def send_special(self, cnt: ControllerPtr, mode: TransMode, special: DatagramSpecialPtr, timeout_ns: int, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_int32:
        return self.dll.AUTDSendSpecial(cnt, mode, special, timeout_ns, err)

    def link_bundle(self, main: LinkPtr, sub: LinkPtr) -> LinkPtr:
        return self.dll.AUTDLinkBundle(main, sub)

    def link_debug(self) -> LinkPtr:
        return self.dll.AUTDLinkDebug()

    def link_debug_with_log_level(self, debug: LinkPtr, level: Level) -> LinkPtr:
        return self.dll.AUTDLinkDebugWithLogLevel(debug, level)

    def link_debug_with_log_func(self, debug: LinkPtr, out_func: ctypes.c_void_p, flush_func: ctypes.c_void_p) -> LinkPtr:
        return self.dll.AUTDLinkDebugWithLogFunc(debug, out_func, flush_func)

    def link_debug_with_timeout(self, debug: LinkPtr, timeout_ns: int) -> LinkPtr:
        return self.dll.AUTDLinkDebugWithTimeout(debug, timeout_ns)

    def link_log(self, link: LinkPtr) -> LinkPtr:
        return self.dll.AUTDLinkLog(link)

    def link_log_with_log_level(self, log: LinkPtr, level: Level) -> LinkPtr:
        return self.dll.AUTDLinkLogWithLogLevel(log, level)

    def link_log_with_log_func(self, log: LinkPtr, out_func: ctypes.c_void_p, flush_func: ctypes.c_void_p) -> LinkPtr:
        return self.dll.AUTDLinkLogWithLogFunc(log, out_func, flush_func)

    def modulation_custom(self, freq_div: int, ptr: ctypes.Array[ctypes.c_double], len: int) -> ModulationPtr:
        return self.dll.AUTDModulationCustom(freq_div, ptr, len)

    def modulation_with_low_pass(self, m: ModulationPtr, n_taps: int, cutoff: float) -> ModulationPtr:
        return self.dll.AUTDModulationWithLowPass(m, n_taps, cutoff)

    def modulation_with_high_pass(self, m: ModulationPtr, n_taps: int, cutoff: float) -> ModulationPtr:
        return self.dll.AUTDModulationWithHighPass(m, n_taps, cutoff)

    def modulation_with_band_pass(self, m: ModulationPtr, n_taps: int, f_low: float, f_high: float) -> ModulationPtr:
        return self.dll.AUTDModulationWithBandPass(m, n_taps, f_low, f_high)

    def modulation_with_band_stop(self, m: ModulationPtr, n_taps: int, f_low: float, f_high: float) -> ModulationPtr:
        return self.dll.AUTDModulationWithBandStop(m, n_taps, f_low, f_high)

    def modulation_fourier(self) -> ModulationPtr:
        return self.dll.AUTDModulationFourier()

    def modulation_fourier_add_component(self, fourier: ModulationPtr, m: ModulationPtr) -> ModulationPtr:
        return self.dll.AUTDModulationFourierAddComponent(fourier, m)

    def modulation_sampling_frequency_division(self, m: ModulationPtr) -> ctypes.c_uint32:
        return self.dll.AUTDModulationSamplingFrequencyDivision(m)

    def modulation_into_datagram(self, m: ModulationPtr) -> DatagramPtr:
        return self.dll.AUTDModulationIntoDatagram(m)

    def modulation_size(self, m: ModulationPtr, err: ctypes.Array[ctypes.c_char]) -> ctypes.c_int32:
        return self.dll.AUTDModulationSize(m, err)

    def modulation_calc(self, m: ModulationPtr, buffer: ctypes.Array[ctypes.c_double], err: ctypes.Array[ctypes.c_char]) -> ctypes.c_int32:
        return self.dll.AUTDModulationCalc(m, buffer, err)

    def modulation_sine(self, freq: int) -> ModulationPtr:
        return self.dll.AUTDModulationSine(freq)

    def modulation_sine_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationSineWithSamplingFrequencyDivision(m, div)

    def modulation_sine_with_amp(self, m: ModulationPtr, amp: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineWithAmp(m, amp)

    def modulation_sine_with_phase(self, m: ModulationPtr, phase: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineWithPhase(m, phase)

    def modulation_sine_with_offset(self, m: ModulationPtr, offset: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineWithOffset(m, offset)

    def modulation_sine_legacy(self, freq: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineLegacy(freq)

    def modulation_sine_legacy_with_amp(self, m: ModulationPtr, amp: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineLegacyWithAmp(m, amp)

    def modulation_sine_legacy_with_offset(self, m: ModulationPtr, offset: float) -> ModulationPtr:
        return self.dll.AUTDModulationSineLegacyWithOffset(m, offset)

    def modulation_sine_legacy_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationSineLegacyWithSamplingFrequencyDivision(m, div)

    def modulation_square(self, freq: int) -> ModulationPtr:
        return self.dll.AUTDModulationSquare(freq)

    def modulation_square_with_low(self, m: ModulationPtr, low: float) -> ModulationPtr:
        return self.dll.AUTDModulationSquareWithLow(m, low)

    def modulation_square_with_high(self, m: ModulationPtr, high: float) -> ModulationPtr:
        return self.dll.AUTDModulationSquareWithHigh(m, high)

    def modulation_square_with_duty(self, m: ModulationPtr, duty: float) -> ModulationPtr:
        return self.dll.AUTDModulationSquareWithDuty(m, duty)

    def modulation_square_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationSquareWithSamplingFrequencyDivision(m, div)

    def modulation_static(self) -> ModulationPtr:
        return self.dll.AUTDModulationStatic()

    def modulation_static_with_amp(self, m: ModulationPtr, amp: float) -> ModulationPtr:
        return self.dll.AUTDModulationStaticWithAmp(m, amp)

    def modulation_static_with_sampling_frequency_division(self, m: ModulationPtr, div: int) -> ModulationPtr:
        return self.dll.AUTDModulationStaticWithSamplingFrequencyDivision(m, div)

    def focus_stm(self, props: STMPropsPtr, points: ctypes.Array[ctypes.c_double], shift: ctypes.Array[ctypes.c_uint8], size: int) -> DatagramPtr:
        return self.dll.AUTDFocusSTM(props, points, shift, size)

    def gain_stm(self, props: STMPropsPtr, gains: ctypes.Array, size: int, mode: GainSTMMode) -> DatagramPtr:
        return self.dll.AUTDGainSTM(props, gains, size, mode)

    def gain_stm_add_gain(self, stm: DatagramPtr, gain: GainPtr) -> DatagramPtr:
        return self.dll.AUTDGainSTMAddGain(stm, gain)

    def stm_props(self, freq: float) -> STMPropsPtr:
        return self.dll.AUTDSTMProps(freq)

    def stm_props_with_sampling_freq(self, freq: float) -> STMPropsPtr:
        return self.dll.AUTDSTMPropsWithSamplingFreq(freq)

    def stm_props_with_sampling_freq_div(self, div: int) -> STMPropsPtr:
        return self.dll.AUTDSTMPropsWithSamplingFreqDiv(div)

    def stm_props_with_sampling_period(self, period_ns: int) -> STMPropsPtr:
        return self.dll.AUTDSTMPropsWithSamplingPeriod(period_ns)

    def stm_props_with_start_idx(self, props: STMPropsPtr, idx: int) -> STMPropsPtr:
        return self.dll.AUTDSTMPropsWithStartIdx(props, idx)

    def stm_props_with_finish_idx(self, props: STMPropsPtr, idx: int) -> STMPropsPtr:
        return self.dll.AUTDSTMPropsWithFinishIdx(props, idx)

    def stm_props_frequency(self, props: STMPropsPtr, size: int) -> ctypes.c_double:
        return self.dll.AUTDSTMPropsFrequency(props, size)

    def stm_props_sampling_frequency(self, props: STMPropsPtr, size: int) -> ctypes.c_double:
        return self.dll.AUTDSTMPropsSamplingFrequency(props, size)

    def stm_props_sampling_frequency_division(self, props: STMPropsPtr, size: int) -> ctypes.c_uint32:
        return self.dll.AUTDSTMPropsSamplingFrequencyDivision(props, size)

    def stm_props_sampling_period(self, props: STMPropsPtr, size: int) -> ctypes.c_uint64:
        return self.dll.AUTDSTMPropsSamplingPeriod(props, size)

    def stm_props_start_idx(self, props: STMPropsPtr) -> ctypes.c_int32:
        return self.dll.AUTDSTMPropsStartIdx(props)

    def stm_props_finish_idx(self, props: STMPropsPtr) -> ctypes.c_int32:
        return self.dll.AUTDSTMPropsFinishIdx(props)
