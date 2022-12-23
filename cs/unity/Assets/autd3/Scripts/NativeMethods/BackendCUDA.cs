// This file was automatically generated from header file
using System;
using System.Runtime.InteropServices;

#if UNITY_2020_2_OR_NEWER
#nullable enable
#endif

namespace AUTD3Sharp.NativeMethods
{
    internal static class BackendCUDA
    {
        private const string DLL = "autd3capi-backend-cuda";

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)] public static extern void AUTDCUDABackend(out IntPtr @out);
    }
}

#if UNITY_2020_2_OR_NEWER
#nullable disable
#endif
