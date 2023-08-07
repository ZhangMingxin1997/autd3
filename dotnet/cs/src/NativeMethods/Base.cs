// This file is autogenerated
using System;
using System.Runtime.InteropServices;

#if UNITY_2020_2_OR_NEWER
#nullable enable
#endif

namespace AUTD3Sharp
{
    namespace NativeMethods
    {
        internal static class Base
        {
            private const string DLL = "autd3capi";

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ControllerBuilderPtr AUTDCreateControllerBuilder();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ControllerBuilderPtr AUTDAddDevice(ControllerBuilderPtr builder, double x, double y, double z, double rz1, double ry, double rz2);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ControllerBuilderPtr AUTDAddDeviceQuaternion(ControllerBuilderPtr builder, double x, double y, double z, double qw, double qx, double qy, double qz);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ControllerPtr AUTDControllerOpenWith(ControllerBuilderPtr builder, LinkPtr link, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDClose(ControllerPtr cnt, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeController(ControllerPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetReadsFPGAInfo(ControllerPtr cnt, [MarshalAs(UnmanagedType.U1)] bool value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetForceFan(ControllerPtr cnt, [MarshalAs(UnmanagedType.U1)] bool value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GeometryPtr AUTDGetGeometry(ControllerPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDGetSoundSpeed(GeometryPtr geo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeed(GeometryPtr geo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeedFromTemp(GeometryPtr geo, double temp, double k, double r, double m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDGetTransFrequency(GeometryPtr geo, uint idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSetTransFrequency(GeometryPtr geo, uint idx, double value, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetTransCycle(GeometryPtr geo, uint idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSetTransCycle(GeometryPtr geo, uint idx, ushort value, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDGetWavelength(GeometryPtr geo, uint idx, double soundSpeed);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDGetAttenuation(GeometryPtr geo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetAttenuation(GeometryPtr geo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDNumTransducers(GeometryPtr geo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDNumDevices(GeometryPtr geo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGeometryCenter(GeometryPtr geo, double[] center);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGeometryCenterOf(GeometryPtr geo, uint devIdx, double[] center);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransPosition(GeometryPtr geo, uint trIdx, double[] pos);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransRotation(GeometryPtr geo, uint trIdx, double[] rot);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransXDirection(GeometryPtr geo, uint trIdx, double[] dir);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransYDirection(GeometryPtr geo, uint trIdx, double[] dir);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransZDirection(GeometryPtr geo, uint trIdx, double[] dir);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetTransModDelay(GeometryPtr geo, uint trIdx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetTransModDelay(GeometryPtr geo, uint trIdx, ushort delay);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDGetFPGAInfo(ControllerPtr cnt, byte[] @out, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern FirmwareInfoListPtr AUTDGetFirmwareInfoListPointer(ControllerPtr cnt, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGetFirmwareInfo(FirmwareInfoListPtr pInfoList, uint idx, byte[] info, bool[] props);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeFirmwareInfoListPointer(FirmwareInfoListPtr pInfoList);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGetLatestFirmware(byte[] latest);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainNull();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainGrouped();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainGroupedAdd(GainPtr groupedGain, uint deviceId, GainPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainGroupedAddByGroup(GainPtr groupedGain, uint[]? deviceIds, ulong deviceIdsLen, GainPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainFocus(double x, double y, double z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainFocusWithAmp(GainPtr focus, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainBessel(double x, double y, double z, double nx, double ny, double nz, double thetaZ);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainBesselWithAmp(GainPtr bessel, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainPlane(double nx, double ny, double nz);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainPlaneWithAmp(GainPtr plane, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainTransducerTest();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainTransducerTestSet(GainPtr transTest, uint id, double phase, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern GainPtr AUTDGainCustom(Drive[]? ptr, ulong len);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDGainIntoDatagram(GainPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDGainCalc(GainPtr gain, GeometryPtr geometry, Drive[] drives, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationStatic();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationStaticWithAmp(ModulationPtr m, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationStaticWithSamplingFrequencyDivision(ModulationPtr m, uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSine(uint freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineWithAmp(ModulationPtr m, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineWithPhase(ModulationPtr m, double phase);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineWithOffset(ModulationPtr m, double offset);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineWithSamplingFrequencyDivision(ModulationPtr m, uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineLegacy(double freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineLegacyWithAmp(ModulationPtr m, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineLegacyWithOffset(ModulationPtr m, double offset);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSineLegacyWithSamplingFrequencyDivision(ModulationPtr m, uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSquare(uint freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSquareWithLow(ModulationPtr m, double low);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSquareWithHigh(ModulationPtr m, double high);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSquareWithDuty(ModulationPtr m, double duty);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationSquareWithSamplingFrequencyDivision(ModulationPtr m, uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ModulationPtr AUTDModulationCustom(uint freqDiv, double[]? ptr, ulong len);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDModulationSamplingFrequencyDivision(ModulationPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDModulationSamplingFrequency(ModulationPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramHeaderPtr AUTDModulationIntoDatagram(ModulationPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDModulationSize(ModulationPtr m, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDModulationCalc(ModulationPtr m, double[] buffer, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern STMPropsPtr AUTDSTMProps(double freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern STMPropsPtr AUTDSTMPropsWithSamplingFreq(double freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern STMPropsPtr AUTDSTMPropsWithSamplingFreqDiv(uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern STMPropsPtr AUTDSTMPropsWithStartIdx(STMPropsPtr props, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern STMPropsPtr AUTDSTMPropsWithFinishIdx(STMPropsPtr props, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDSTMPropsFrequency(STMPropsPtr props, ulong size);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern double AUTDSTMPropsSamplingFrequency(STMPropsPtr props, ulong size);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDSTMPropsSamplingFrequencyDivision(STMPropsPtr props, ulong size);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSTMPropsStartIdx(STMPropsPtr props);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSTMPropsFinishIdx(STMPropsPtr props);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDFocusSTM(STMPropsPtr props, double[]? points, byte[]? shift, ulong size);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDGainSTMWithMode(STMPropsPtr props, GainSTMMode mode);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDGainSTM(STMPropsPtr props);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDGainSTMAddGain(DatagramBodyPtr stm, GainPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramSpecialPtr AUTDSynchronize();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramSpecialPtr AUTDClear();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramSpecialPtr AUTDUpdateFlags();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramSpecialPtr AUTDStop();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramSpecialPtr AUTDModDelayConfig();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramHeaderPtr AUTDCreateSilencer(ushort step);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern DatagramBodyPtr AUTDCreateAmplitudes(double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSend(ControllerPtr cnt, TransMode mode, DatagramHeaderPtr header, DatagramBodyPtr body, long timeoutNs, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSendSpecial(ControllerPtr cnt, TransMode mode, DatagramSpecialPtr special, long timeoutNs, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkDebug();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkDebugWithLogLevel(LinkPtr debug, Level level);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkDebugWithLogFunc(LinkPtr debug, IntPtr outFunc, IntPtr flushFunc);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkDebugWithTimeout(LinkPtr debug, ulong timeoutNs);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkLog(LinkPtr link);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkLogWithLogLevel(LinkPtr log, Level level);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern LinkPtr AUTDLinkLogWithLogFunc(LinkPtr log, IntPtr outFunc, IntPtr flushFunc);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct ControllerBuilderPtr
    {
        public IntPtr _0;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct FirmwareInfoListPtr
    {
        public IntPtr _0;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Drive
    {
        public double Phase;
        public double Amp;
    }

}

#if UNITY_2020_2_OR_NEWER
#nullable disable
#endif


