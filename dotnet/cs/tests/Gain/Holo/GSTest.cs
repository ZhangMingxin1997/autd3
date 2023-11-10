/*
 * File: GSTest.cs
 * Project: Holo
 * Created Date: 25/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

using AUTD3Sharp.Gain.Holo;

namespace tests.Gain.Holo;

public class GSTest
{
    [Fact]
    public async Task GS()
    {
        var autd = await Controller.Builder().AddDevice(new AUTD3(Vector3d.zero, Vector3d.zero)).OpenWithAsync(Audit.Builder());

        var backend = new NalgebraBackend();
        var g = new GS<NalgebraBackend>(backend)
            .AddFocus(autd.Geometry.Center + new Vector3d(30, 0, 150), 0.5)
            .AddFociFromIter(new double[] { -40 }.Select(x => (autd.Geometry.Center + new Vector3d(x, 0, 150), 0.5)))
            .WithRepeat(100)
            .WithConstraint(new AUTD3Sharp.Gain.Holo.Uniform(0.5));

        Assert.True(await autd.SendAsync(g));

        foreach (var dev in autd.Geometry)
        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(dev.Idx, 0);
            Assert.All(duties, d => Assert.Equal(85, d));
            Assert.Contains(phases, p => p != 0);
        }
    }

    [IgnoreIfCUDAIsNotFoundFact]
    public async Task GSWithCUDA()
    {
        var autd = await Controller.Builder().AddDevice(new AUTD3(Vector3d.zero, Vector3d.zero)).OpenWithAsync(Audit.Builder());

        var backend = new CUDABackend();
        var g = new GS<CUDABackend>(backend)
            .AddFocus(autd.Geometry.Center + new Vector3d(30, 0, 150), 0.5)
            .AddFociFromIter(new double[] { -40 }.Select(x => (autd.Geometry.Center + new Vector3d(x, 0, 150), 0.5)))
            .WithRepeat(100)
            .WithConstraint(new AUTD3Sharp.Gain.Holo.Uniform(0.5));

        Assert.True(await autd.SendAsync(g));

        foreach (var dev in autd.Geometry)
        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(dev.Idx, 0);
            Assert.All(duties, d => Assert.Equal(85, d));
            Assert.Contains(phases, p => p != 0);
        }
    }
}