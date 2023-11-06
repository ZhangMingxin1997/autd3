/*
 * File: FocusSTMTest.cs
 * Project: STM
 * Created Date: 25/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

using AUTD3Sharp.STM;

namespace tests.STM;

public class FocusSTMTest
{
    [Fact]
    public void TestFocusSTM()
    {
        var autd = AUTDTest.CreateController();

        const double radius = 30.0;
        const int size = 2;
        var center = autd.Geometry.Center + new Vector3d(0, 0, 150);
        var stm = new FocusSTM(1)
            .AddFociFromIter(Enumerable.Range(0, size).Select(i => 2 * Math.PI * i / size).Select(theta =>
                (center + radius * new Vector3d(Math.Cos(theta), Math.Sin(theta), 0), (byte)0)));
        Assert.True(autd.Send(stm));

        foreach (var dev in autd.Geometry)
        {
            Assert.False(autd.Link<Audit>().IsStmGainMode(dev.Idx));
        }

        Assert.Equal(1, stm.Frequency);
        Assert.Equal(2, stm.SamplingFrequency);
        Assert.Equal(10240000u, stm.SamplingFrequencyDivision);
        Assert.Equal(TimeSpan.FromMicroseconds(500000), stm.SamplingPeriod);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(10240000u, autd.Link<Audit>().StmFrequencyDivision(dev.Idx));
        }

        Assert.Null(stm.StartIdx);
        Assert.Null(stm.FinishIdx);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(-1, autd.Link<Audit>().StmStartIdx(dev.Idx));
            Assert.Equal(-1, autd.Link<Audit>().StmFinishIdx(dev.Idx));
        }

        stm = stm.WithStartIdx(0);
        Assert.True(autd.Send(stm));
        Assert.Equal((ushort)0, stm.StartIdx);
        Assert.Null(stm.FinishIdx);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(0, autd.Link<Audit>().StmStartIdx(dev.Idx));
            Assert.Equal(-1, autd.Link<Audit>().StmFinishIdx(dev.Idx));
        }

        stm = stm.WithStartIdx(null).WithFinishIdx(0);
        Assert.True(autd.Send(stm));
        Assert.Null(stm.StartIdx);
        Assert.Equal((ushort)0, stm.FinishIdx);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(-1, autd.Link<Audit>().StmStartIdx(dev.Idx));
            Assert.Equal(0, autd.Link<Audit>().StmFinishIdx(dev.Idx));
        }

        stm = FocusSTM.WithSamplingFrequencyDivision(512).AddFocus(center).AddFocus(center);
        Assert.True(autd.Send(stm));
        Assert.Equal(20000.0, stm.Frequency);
        Assert.Equal(2 * 20000.0, stm.SamplingFrequency);
        Assert.Equal(512u, stm.SamplingFrequencyDivision);
        Assert.Equal(TimeSpan.FromMicroseconds(25), stm.SamplingPeriod);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(512u, autd.Link<Audit>().StmFrequencyDivision(dev.Idx));
        }

        stm = FocusSTM.WithSamplingFrequency(20e3).AddFocus(center).AddFocus(center);
        Assert.True(autd.Send(stm));
        Assert.Equal(10000, stm.Frequency);
        Assert.Equal(2 * 10000, stm.SamplingFrequency);
        Assert.Equal(1024u, stm.SamplingFrequencyDivision);
        Assert.Equal(TimeSpan.FromMicroseconds(50), stm.SamplingPeriod);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(1024u, autd.Link<Audit>().StmFrequencyDivision(dev.Idx));
        }

        stm = FocusSTM.WithSamplingPeriod(TimeSpan.FromMicroseconds(25)).AddFocus(center).AddFocus(center);
        Assert.True(autd.Send(stm));
        Assert.Equal(20000.0, stm.Frequency);
        Assert.Equal(2 * 20000.0, stm.SamplingFrequency);
        Assert.Equal(512u, stm.SamplingFrequencyDivision);
        Assert.Equal(TimeSpan.FromMicroseconds(25), stm.SamplingPeriod);
        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(512u, autd.Link<Audit>().StmFrequencyDivision(dev.Idx));
        }


        foreach (var dev in autd.Geometry)
        {
            Assert.Equal(2u, autd.Link<Audit>().StmCycle(dev.Idx));
            {
                var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(dev.Idx, 0);
                Assert.Contains(duties, d => d != 0);
                Assert.Contains(phases, p => p != 0);
            }
            {
                var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(dev.Idx, 1);
                Assert.Contains(duties, d => d != 0);
                Assert.Contains(phases, p => p != 0);
            }
        }
    }
}