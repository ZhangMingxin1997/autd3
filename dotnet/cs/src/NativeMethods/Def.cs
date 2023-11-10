// <auto-generated>
// This code is generated by csbindgen.
// DON'T CHANGE THIS DIRECTLY.
// </auto-generated>
#pragma warning disable CS8500
#pragma warning disable CS8981
using System;
using System.Runtime.InteropServices;


namespace AUTD3Sharp
{
    internal static unsafe partial class NativeMethodsDef
    {
        const string __DllName = "autd3capi_def";

        internal const uint NUM_TRANS_IN_UNIT = 249;
        internal const uint NUM_TRANS_IN_X = 18;
        internal const uint NUM_TRANS_IN_Y = 14;
        internal const double TRANS_SPACING_MM = 10.16;
        internal const double DEVICE_HEIGHT_MM = 151.4;
        internal const double DEVICE_WIDTH_MM = 192;
        internal const uint FPGA_CLK_FREQ = 20480000;
        internal const double ULTRASOUND_FREQUENCY = 40000;
        internal const int AUTD3_TRUE = 1;
        internal const int AUTD3_FALSE = 0;


        [DllImport(__DllName, EntryPoint = "AUTDGetErr", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void AUTDGetErr(IntPtr src, byte* dst);


    }



}
    