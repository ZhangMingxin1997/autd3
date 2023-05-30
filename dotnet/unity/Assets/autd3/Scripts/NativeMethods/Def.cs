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
        internal static class Def
        {
            private const string DLL = "autd3capi_def";

            public const uint NumTransInUnit = 249;

            public const uint NumTransInX = 18;

            public const uint NumTransInY = 14;

            public const float TransSpacingMm = 10.16f;

            public const float DeviceHeightMm = 151.4f;

            public const float DeviceWidthMm = 192.0f;

            public const uint FpgaClkFreq = 163840000;

            public const uint FpgaSubClkFreq = 20480000;

            public const int Err = -1;

            public const int True = 1;

            public const int False = 0;
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

    public enum TimerStrategy : byte
    {
        Sleep = 0,
        NativeTimer = 1,
        BusyWait = 2,
    }

}

#if UNITY_2020_2_OR_NEWER
#nullable disable
#endif


