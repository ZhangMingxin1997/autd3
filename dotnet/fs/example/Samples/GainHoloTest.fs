﻿// File: GainHoloTest.fs
// Project: Samples
// Created Date: 03/02/2023
// Author: Shun Suzuki
// -----
// Last Modified: 18/04/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
// 

namespace Samples

open AUTD3Sharp
open AUTD3Sharp.Gain.Holo
open AUTD3Sharp.Modulation
open AUTD3Sharp.Utils

module GainHoloTest =
    let Test (autd : Controller) = 
        (new SilencerConfig()) |> autd.Send |> ignore

        let m = new Sine 150;

        let center = autd.Geometry.Center + Vector3d(0, 0, 150);
        let g = (new GSPAT()).WithConstraint(new Uniform());
        g.AddFocus(center + 20.0 * Vector3d.UnitX, 1.0);
        g.AddFocus(center - 20.0 * Vector3d.UnitX, 1.0);

        (m, g) |> autd.Send |> ignore