// This file was automatically generated from header file
using System;
using System.Runtime.InteropServices;

#if UNITY_2020_2_OR_NEWER
#nullable enable
#endif

namespace AUTD3Sharp.NativeMethods
{
    internal static class Base
    {
        private const string DLL = "autd3capi";

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetLogLevel(int level);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetDefaultLogger(IntPtr @out, IntPtr flush);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDCreateController(out IntPtr @out, byte driverVersion);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDOpenController(IntPtr handle, IntPtr link);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDAddDevice(IntPtr handle, float x, float y, float z, float rz1, float ry, float rz2);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDAddDeviceQuaternion(IntPtr handle, float x, float y, float z, float qw, float qx, float qy, float qz);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDClose(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeController(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDIsOpen(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDGetForceFan(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDGetReadsFPGAInfo(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ulong AUTDGetAckCheckTimeout(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ulong AUTDGetSendInterval(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetReadsFPGAInfo(IntPtr handle, [MarshalAs(UnmanagedType.U1)] bool readsFpgaInfo);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetAckCheckTimeout(IntPtr handle, ulong timeout);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSendInterval(IntPtr handle, ulong interval);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetForceFan(IntPtr handle, [MarshalAs(UnmanagedType.U1)] bool force);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetSoundSpeed(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeed(IntPtr handle, float soundSpeed);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetSoundSpeedFromTemp(IntPtr handle, float temp, float k, float r, float m);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetTransFrequency(IntPtr handle, int transIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetTransFrequency(IntPtr handle, int transIdx, float frequency);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetTransCycle(IntPtr handle, int transIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetTransCycle(IntPtr handle, int transIdx, ushort cycle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetWavelength(IntPtr handle, int transIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDGetAttenuation(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetAttenuation(IntPtr handle, float attenuation);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDGetFPGAInfo(IntPtr handle, byte[]? @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDNumTransducers(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDNumDevices(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGeometryCenter(IntPtr handle, out float x, out float y, out float z);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransPosition(IntPtr handle, int transIdx, out float x, out float y, out float z);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransXDirection(IntPtr handle, int transIdx, out float x, out float y, out float z);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransYDirection(IntPtr handle, int transIdx, out float x, out float y, out float z);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDTransZDirection(IntPtr handle, int transIdx, out float x, out float y, out float z);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDGetFirmwareInfoListPointer(IntPtr handle, out IntPtr @out);
        [DllImport(DLL, CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGetFirmwareInfo(IntPtr pFirmInfoList, int index, System.Text.StringBuilder? info);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFreeFirmwareInfoListPointer(IntPtr pFirmInfoList);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainNull(out IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainGrouped(out IntPtr gain, IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainGroupedAdd(IntPtr groupedGain, int deviceId, IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainFocus(out IntPtr gain, float x, float y, float z, float amp);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainBesselBeam(out IntPtr gain, float x, float y, float z, float nX, float nY, float nZ, float thetaZ, float amp);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainPlaneWave(out IntPtr gain, float nX, float nY, float nZ, float amp);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainTransducerTest(out IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainTransducerTestSet(IntPtr gain, int trIdx, float amp, float phase);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainCustom(out IntPtr gain, float[]? amp, float[]? phase, ulong size);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteGain(IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationStatic(out IntPtr mod, float amp);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSine(out IntPtr mod, int freq, float amp, float offset);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSineSquared(out IntPtr mod, int freq, float amp, float offset);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSineLegacy(out IntPtr mod, float freq, float amp, float offset);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSquare(out IntPtr mod, int freq, float low, float high, float duty);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationLPF(out IntPtr mod, IntPtr modIn);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationCustom(out IntPtr mod, byte[]? buffer, ulong size, uint freqDiv);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDModulationSamplingFrequencyDivision(IntPtr mod);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModulationSetSamplingFrequencyDivision(IntPtr mod, uint freqDiv);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDModulationSamplingFrequency(IntPtr mod);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteModulation(IntPtr mod);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTM(out IntPtr @out, float soundSpeed);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTM(out IntPtr @out, IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDFocusSTMAdd(IntPtr stm, float x, float y, float z, byte shift);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainSTMAdd(IntPtr stm, IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetGainSTMMode(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetGainSTMMode(IntPtr stm, ushort mode);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSTMSetFrequency(IntPtr stm, float freq);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSTMGetStartIdx(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern int AUTDSTMGetFinishIdx(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSTMSetStartIdx(IntPtr stm, int startIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSTMSetFinishIdx(IntPtr stm, int finishIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSTMFrequency(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSTMSamplingFrequency(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern uint AUTDSTMSamplingFrequencyDivision(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSTMSetSamplingFrequencyDivision(IntPtr stm, uint freqDiv);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSTM(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSynchronize(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDClear(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDUpdateFlags(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDStop(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDModDelayConfig(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSpecialData(IntPtr data);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDCreateSilencer(out IntPtr @out, ushort step, ushort cycle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSilencer(IntPtr config);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSend(IntPtr handle, IntPtr header, IntPtr body);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)][return: MarshalAs(UnmanagedType.U1)] public static extern bool AUTDSendSpecial(IntPtr handle, IntPtr special);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSendAsync(IntPtr handle, IntPtr header, IntPtr body);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSendSpecialAsync(IntPtr handle, IntPtr special);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ushort AUTDGetModDelay(IntPtr handle, int transIdx);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetModDelay(IntPtr handle, int transIdx, ushort delay);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDCreateAmplitudes(out IntPtr @out, float amp);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteAmplitudes(IntPtr amplitudes);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSetMode(IntPtr handle, byte mode);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTM(out IntPtr @out);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTMSetStrategy(IntPtr stm, byte strategy);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTMAdd(IntPtr stm, IntPtr gain);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTMStart(out IntPtr handle, IntPtr stm, IntPtr cnt);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTMFinish(IntPtr handle);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSoftwareSTMSetFrequency(IntPtr stm, float freq);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSoftwareSTMFrequency(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ulong AUTDSoftwareSTMPeriod(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern float AUTDSoftwareSTMSamplingFrequency(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern ulong AUTDSoftwareSTMSamplingPeriod(IntPtr stm);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDSoftwareSTMSetSamplingPeriod(IntPtr stm, ulong period);
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDDeleteSoftwareSTM(IntPtr stm);
    }
}

#if UNITY_2020_2_OR_NEWER
#nullable disable
#endif