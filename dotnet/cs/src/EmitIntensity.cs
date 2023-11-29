/*
 * File: EmitIntensity.cs
 * Project: src
 * Created Date: 12/11/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 29/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

#if UNITY_2018_3_OR_NEWER
#define USE_SINGLE
#endif

using AUTD3Sharp.NativeMethods;

#if USE_SINGLE
using float_t = System.Single;
#else
using float_t = System.Double;
#endif

using System.Runtime.InteropServices;

namespace AUTD3Sharp
{
    [StructLayout(LayoutKind.Sequential)]
    public readonly struct EmitIntensity
    {
        public byte Value { get; }

        public static readonly EmitIntensity Max = new EmitIntensity(0xFF);
        public static readonly EmitIntensity Min = new EmitIntensity(0x00);

        public static readonly float_t DefaultCorrectedAlpha = NativeMethodsDef.DEFAULT_CORRECTED_ALPHA;

        public EmitIntensity(byte value)
        {
            Value = value;
        }

        public static EmitIntensity NewWithCorrectionAlpha(byte value, float_t alpha) => new EmitIntensity(NativeMethodsDef.AUTDEmitIntensityNewWithCorrectionAlpha(value, alpha));

        public static EmitIntensity NewWithCorrection(byte value) => NewWithCorrectionAlpha(value, NativeMethodsDef.DEFAULT_CORRECTED_ALPHA);
    }
}