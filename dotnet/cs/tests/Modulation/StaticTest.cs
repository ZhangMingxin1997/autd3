/*
 * File: StaticTest.cs
 * Project: Modulation
 * Created Date: 25/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

namespace tests.Modulation;

public class StaticTest
{
    [Fact]
    public async Task Static()
    {
        var autd = await Controller.Builder().AddDevice(new AUTD3(Vector3d.zero, Vector3d.zero)).OpenWithAsync(Audit.Builder());

        Assert.True(await autd.SendAsync(new Static().WithAmp(0.2)));

        foreach (var dev in autd.Geometry)
        {
            var mod = autd.Link<Audit>().Modulation(dev.Idx);
#pragma warning disable IDE0230
            var modExpext = new byte[] { 32, 32 };
#pragma warning restore IDE0230
            Assert.Equal(modExpext, mod);
            Assert.Equal(5120u, autd.Link<Audit>().ModulationFrequencyDivision(dev.Idx));
        }
    }
}