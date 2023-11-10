/*
 * File: TransTestTest.cs
 * Project: Gain
 * Created Date: 25/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

namespace tests.Gain;

public class TransTestTest
{
    [Fact]
    public async Task TransTest()
    {
        var autd = await AUTDTest.CreateController();

        Assert.True(await autd.SendAsync(new TransducerTest().Set(0, 0, Math.PI, 0.5).Set(1, 248, Math.PI, 0.5)));

        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(0, 0);
            Assert.Equal(85, duties[0]);
            Assert.Equal(256, phases[0]);
            Assert.All(duties.Skip(1), d => Assert.Equal(0, d));
            Assert.All(phases.Skip(1), p => Assert.Equal(0, p));
        }

        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(1, 0);
            Assert.Equal(85, duties[autd.Geometry[1].NumTransducers - 1]);
            Assert.Equal(256, phases[autd.Geometry[1].NumTransducers - 1]);
            Assert.All(duties.Take(autd.Geometry[1].NumTransducers - 1), d => Assert.Equal(0, d));
            Assert.All(phases.Take(autd.Geometry[1].NumTransducers - 1), p => Assert.Equal(0, p));
        }
    }
}