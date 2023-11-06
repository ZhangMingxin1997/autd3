﻿// File: Program.fs
// Project: Group
// Created Date: 14/09/2023
// Author: Shun Suzuki
// -----
// Last Modified: 06/11/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2023 Shun Suzuki. All rights reserved.
// 

open AUTD3Sharp.Utils
open AUTD3Sharp
open AUTD3Sharp.Link
open AUTD3Sharp.Gain
open AUTD3Sharp.Modulation

let autd = Controller.Builder()
            .AddDevice(new AUTD3(Vector3d.zero, Vector3d.zero))
            .OpenWith(Nop.Builder());

let cx = autd.Geometry.Center.x;
let g1 = new Focus(autd.Geometry.Center + Vector3d(0., 0., 150.));
let g2 = new Null();

let grouping (dev: Device) (tr: Transducer) =
    if (tr.Position.x < cx) then "focus" :> obj else "null" :> obj
let g = (new Group(grouping)).Set("focus", g1).Set("null", g2);
let m = new Sine(150);

(m, g) |> autd.Send |> ignore;
