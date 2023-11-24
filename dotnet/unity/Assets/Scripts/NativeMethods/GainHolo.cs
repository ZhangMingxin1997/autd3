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
    internal static unsafe partial class NativeMethodsGainHolo
    {
        const string __DllName = "autd3capi_gain_holo";



        [DllImport(__DllName, EntryPoint = "AUTDGainHoloConstraintDotCare", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern EmissionConstraintPtr AUTDGainHoloConstraintDotCare();

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloConstraintNormalize", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern EmissionConstraintPtr AUTDGainHoloConstraintNormalize();

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloConstraintUniform", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern EmissionConstraintPtr AUTDGainHoloConstraintUniform(byte intensity);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloConstraintClamp", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern EmissionConstraintPtr AUTDGainHoloConstraintClamp(byte min_v, byte max_v);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGreedy", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGreedy(float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGreedyWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGreedyWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGreedyWithPhaseDiv", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGreedyWithPhaseDiv(GainPtr holo, uint div);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGS", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGS(BackendPtr backend, float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGSWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGSWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGSWithRepeat", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGSWithRepeat(GainPtr holo, uint repeat);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGSPAT", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGSPAT(BackendPtr backend, float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGSPATWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGSPATWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloGSPATWithRepeat", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloGSPATWithRepeat(GainPtr holo, uint repeat);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSPLToPascal", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern float AUTDGainHoloSPLToPascal(float value);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloPascalToSPL", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern float AUTDGainHoloPascalToSPL(float value);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLM", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLM(BackendPtr backend, float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithEps1", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithEps1(GainPtr holo, float eps);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithEps2", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithEps2(GainPtr holo, float eps);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithTau", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithTau(GainPtr holo, float tau);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithKMax", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithKMax(GainPtr holo, uint k_max);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloLMWithInitial", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloLMWithInitial(GainPtr holo, float* initial_ptr, ulong len);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloNaive", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloNaive(BackendPtr backend, float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloNaiveWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloNaiveWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDNalgebraBackend", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern BackendPtr AUTDNalgebraBackend();

        [DllImport(__DllName, EntryPoint = "AUTDDeleteNalgebraBackend", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void AUTDDeleteNalgebraBackend(BackendPtr backend);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSDP", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloSDP(BackendPtr backend, float* points, float* amps, ulong size);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSDPWithConstraint", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloSDPWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSDPWithAlpha", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloSDPWithAlpha(GainPtr holo, float alpha);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSDPWithLambda", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloSDPWithLambda(GainPtr holo, float lambda);

        [DllImport(__DllName, EntryPoint = "AUTDGainHoloSDPWithRepeat", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern GainPtr AUTDGainHoloSDPWithRepeat(GainPtr holo, uint repeat);


    }



}
    