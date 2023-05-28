// This file is autogenerated
using System;
using System.Runtime.InteropServices;

namespace AUTD3Sharp
{
    namespace NativeMethods
    {
        internal static class Base
        {
            private const string DLL = "autd3capi";

            public const uint NumTransInUnit = 249;

            public const uint NumTransInX = 18;

            public const uint NumTransInY = 14;

            public const float TransSpacingMm = 10.16f;

            public const float DeviceHeight = 151.4f;

            public const float DeviceWidth = 192.0f;

            public const uint FpgaClkFreq = 163840000;

            public const uint FpgaSubClkFreq = 20480000;

            public const int Err = -1;

            public const int True = 1;

            public const int False = 0;

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDCreateGeometryBuilder();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDAddDevice(IntPtr builder, float x, float y, float z, float rz1, float ry, float rz2);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDAddDeviceQuaternion(IntPtr builder, float x, float y, float z, float qw, float qx, float qy, float qz);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDBuildGeometry(IntPtr builder, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDOpenController(IntPtr geometry, IntPtr link, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDClose(IntPtr cnt, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeController(IntPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetReadsFPGAInfo(IntPtr cnt, [MarshalAs(UnmanagedType.U1)] bool value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetForceFan(IntPtr cnt, [MarshalAs(UnmanagedType.U1)] bool value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetSoundSpeed(IntPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeed(IntPtr cnt, float value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeedFromTemp(IntPtr cnt, float temp, float k, float r, float m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetTransFrequency(IntPtr cnt, uint idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSetTransFrequency(IntPtr cnt, uint idx, float value, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetTransCycle(IntPtr cnt, uint idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSetTransCycle(IntPtr cnt, uint idx, ushort value, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetWavelength(IntPtr cnt, uint idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetAttenuation(IntPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetAttenuation(IntPtr cnt, float value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDGetFPGAInfo(IntPtr cnt, byte[]? @out, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDNumTransducers(IntPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDNumDevices(IntPtr cnt);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGeometryCenter(IntPtr cnt, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGeometryCenterOf(IntPtr cnt, uint devIdx, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransPosition(IntPtr cnt, uint trIdx, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransXDirection(IntPtr cnt, uint trIdx, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransYDirection(IntPtr cnt, uint trIdx, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransZDirection(IntPtr cnt, uint trIdx, out float x, out float y, out float z);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetTransModDelay(IntPtr cnt, uint trIdx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetTransModDelay(IntPtr cnt, uint trIdx, ushort delay);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGetFirmwareInfoListPointer(IntPtr cnt, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGetFirmwareInfo(IntPtr pInfoList, uint idx, byte[] info, out bool isValid, out bool isSupported);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeFirmwareInfoListPointer(IntPtr pInfoList);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGetLatestFirmware(byte[] latest);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainNull();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainGrouped();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainGroupedAdd(IntPtr groupedGain, uint deviceId, IntPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainFocus(float x, float y, float z, float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainBesselBeam(float x, float y, float z, float nx, float ny, float nz, float thetaZ, float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainPlaneWave(float nx, float ny, float nz, float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainTransducerTest();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainTransducerTestSet(IntPtr transTest, uint id, float phase, float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainCustom(float[]? amp, float[]? phase, ulong size);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteGain(IntPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationStatic(float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationSine(uint freq, float amp, float offset);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationSineSquared(uint freq, float amp, float offset);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationSineLegacy(float freq, float amp, float offset);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationSquare(uint freq, float low, float high, float duty);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModulationCustom(float[]? amp, ulong size, uint freqDiv);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDModulationSamplingFrequencyDivision(IntPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSetSamplingFrequencyDivision(IntPtr m, uint freqDiv);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDModulationSamplingFrequency(IntPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteModulation(IntPtr m);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDFocusSTM();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTMAdd(IntPtr stm, float x, float y, float z, byte shift);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDFocusSTMSetFrequency(IntPtr stm, float freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDFocusSTMGetStartIdx(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDFocusSTMGetFinishIdx(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTMSetStartIdx(IntPtr stm, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTMSetFinishIdx(IntPtr stm, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDFocusSTMFrequency(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDFocusSTMSamplingFrequency(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDFocusSTMSamplingFrequencyDivision(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTMSetSamplingFrequencyDivision(IntPtr stm, uint freqDiv);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteFocusSTM(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainSTM();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMAdd(IntPtr stm, IntPtr gain);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMSetMode(IntPtr stm, GainSTMMode mode);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGainSTMSetFrequency(IntPtr stm, float freq);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDGainSTMGetStartIdx(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDGainSTMGetFinishIdx(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMSetStartIdx(IntPtr stm, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMSetFinishIdx(IntPtr stm, int idx);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGainSTMFrequency(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGainSTMSamplingFrequency(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDGainSTMSamplingFrequencyDivision(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMSetSamplingFrequencyDivision(IntPtr stm, uint freqDiv);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteGainSTM(IntPtr stm);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDSynchronize();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDClear();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDUpdateFlags();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDStop();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDModDelayConfig();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSpecialData(IntPtr special);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDCreateSilencer(ushort step);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSilencer(IntPtr silencer);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDCreateAmplitudes(float amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteAmplitudes(IntPtr amplitudes);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSend(IntPtr cnt, TransMode mode, IntPtr header, IntPtr body, long timeoutNs, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSendSpecial(IntPtr cnt, TransMode mode, IntPtr special, long timeoutNs, byte[] err);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDLinkDebug();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDLinkDebugLogLevel(IntPtr builder, Level level);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDLinkDebugLogFunc(IntPtr builder, Level level, IntPtr outFunc, IntPtr flushFunc);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDLinkDebugTimeout(IntPtr builder, ulong timeoutNs);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDLinkDebugBuild(IntPtr builder);
        }
    }

    public enum GainSTMMode : byte
    {
        PhaseDutyFull = 0,
        PhaseFull = 1,
        PhaseHalf = 2,
    }

    public enum TransMode : byte
    {
        Legacy = 0,
        Advanced = 1,
        AdvancedPhase = 2,
    }

    public enum Level : byte
    {
        Critical = 0,
        Error = 1,
        Warn = 2,
        Info = 3,
        Debug = 4,
        Trace = 5,
        Off = 6,
    }
}
