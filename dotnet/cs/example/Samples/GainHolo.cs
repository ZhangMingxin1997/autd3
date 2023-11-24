﻿/*
 * File: GainHolo.cs
 * Project: Test
 * Created Date: 30/04/2021
 * Author: Shun Suzuki
 * -----
 * Last Modified: 24/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
 * 
 */

using AUTD3Sharp;
using AUTD3Sharp.Gain.Holo;
using AUTD3Sharp.Modulation;
using AUTD3Sharp.Utils;

namespace Samples;

internal static class GainHoloTest
{
    public static async Task Test<T>(Controller<T> autd)
    {
        var config = new Silencer();
        await autd.SendAsync(config);

        var center = autd.Geometry.Center + new Vector3d(0, 0, 150);

        var backend = new NalgebraBackend();
        var g = new GSPAT<NalgebraBackend>(backend).WithConstraint(new Uniform(EmitIntensity.Max))
            .AddFocus(center + 20.0 * Vector3d.UnitX, Amplitude.NewPascal(5e3))
            .AddFocus(center - 20.0 * Vector3d.UnitX, Amplitude.NewPascal(5e3));

        var m = new Sine(150);

        await autd.SendAsync(m, g);
    }
}
