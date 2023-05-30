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
        internal static class GainHolo
        {
            private const string DLL = "autd3capi_gain_holo";

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDDefaultBackend();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloSDP(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPAlpha(IntPtr holo, double alpha);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPLambda(IntPtr holo, double lambda);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPRepeat(IntPtr holo, uint repeat);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloSDPSetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloEVP(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPGamma(IntPtr holo, double gamma);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloEVPSetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloGS(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSRepeat(IntPtr holo, uint repeat);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSSetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloGSPAT(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATRepeat(IntPtr holo, uint repeat);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGSPATSetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloNaive(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloNaiveAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloNaiveSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloNaiveSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloNaiveSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloNaiveSetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloGreedy();

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedyPhaseDiv(IntPtr holo, uint div);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedyAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedySetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedySetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedySetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloGreedySetClampConstraint(IntPtr holo, double min, double max);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr AUTDGainHoloLM(IntPtr backend);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMEps1(IntPtr holo, double eps1);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMEps2(IntPtr holo, double eps2);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMTau(IntPtr holo, double tau);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMKMax(IntPtr holo, uint kMax);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMInitial(IntPtr holo, double[]? ptr, ulong len);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMAdd(IntPtr holo, double x, double y, double z, double amp);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMSetDotCareConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMSetNormalizeConstraint(IntPtr holo);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMSetUniformConstraint(IntPtr holo, double value);

            [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDGainHoloLMSetClampConstraint(IntPtr holo, double min, double max);
        }
    }

}

#if UNITY_2020_2_OR_NEWER
#nullable disable
#endif


