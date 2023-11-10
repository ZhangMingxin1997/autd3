/*
 * File: ModulationTest.cs
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

public class ModulationTest
{
    public class Burst : AUTD3Sharp.Modulation.Modulation
    {
        public Burst() : base(5120)
        {
        }

        public override double[] Calc()
        {
            var buf = new double[10];
            buf[0] = 1;
            return buf;
        }
    }

    [Fact]
    public async Task Modulation()
    {
        var autd = await Controller.Builder().AddDevice(new AUTD3(Vector3d.zero, Vector3d.zero)).OpenWithAsync(Audit.Builder());

        Assert.True(await autd.SendAsync(new Burst()));
        foreach (var dev in autd.Geometry)
        {
            var mod = autd.Link<Audit>().Modulation(dev.Idx);
            var modExpext = new byte[] { 255, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            Assert.Equal(modExpext, mod);
            Assert.Equal(5120u, autd.Link<Audit>().ModulationFrequencyDivision(dev.Idx));
        }
    }
}
