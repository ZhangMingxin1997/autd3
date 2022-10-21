﻿/*
 * File: FocusTest.cs
 * Project: Test
 * Created Date: 30/04/2021
 * Author: Shun Suzuki
 * -----
 * Last Modified: 21/10/2022
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 * 
 */

using AUTD3Sharp;
using AUTD3Sharp.Gain;
using AUTD3Sharp.Modulation;
using AUTD3Sharp.Utils;

namespace Samples;

internal static class FocusTest
{
    public static void Test(Controller autd)
    {
        var config = new SilencerConfig();
        autd.Send(config);

        var mod = new Sine(150);
        var gain = new Focus(autd.Geometry.Center + new Vector3d(0, 0, 150));
        autd.Send(mod, gain);
    }
}
