/*
 * File: GroupTest.cs
 * Project: Gain
 * Created Date: 25/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/10/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

namespace tests.Gain;

public class GroupTest
{
    [Fact]
    public void Group()
    {
        var autd = AUTDTest.CreateController();

        var cx = autd.Geometry.Center.x;

        Assert.True(autd.Send(new Group((_, tr) => tr.Position.x switch
        {
            var x when x < cx => "uniform",
            _ => "null"
        }).Set("uniform", new Uniform(0.5).WithPhase(Math.PI)).Set("null", new Null())));

        foreach (var dev in autd.Geometry)
        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(dev.Idx, 0);
            foreach (var tr in dev)
            {
                if (tr.Position.x < cx)
                {
                    Assert.Equal(680, duties[tr.LocalIdx]);
                    Assert.Equal(2048, phases[tr.LocalIdx]);
                }
                else
                {
                    Assert.Equal(8, duties[tr.LocalIdx]);
                    Assert.Equal(0, phases[tr.LocalIdx]);
                }
            }
        }
    }

    [Fact]
    public void GroupUnknownKey()
    {
        var autd = AUTDTest.CreateController();

        var exception = Record.Exception(() =>
        {
            autd.Send(new Group((_, _) => "null").Set("uniform", new Uniform(0.5).WithPhase(Math.PI)).Set("null", new Null()));
        });

        if (exception == null) Assert.Fail("Exception is expected");
        Assert.Equal(typeof(AUTDException), exception.GetType());
        Assert.Equal("AUTDException: Unknown group key", exception.Message);
    }

    [Fact]
    public void GroupUnspecifiedKey()
    {
        var autd = AUTDTest.CreateController();

        var exception = Record.Exception(() =>
        {
            autd.Send(new Group((_, _) => "null"));
        });

        if (exception == null) Assert.Fail("Exception is expected");
        Assert.Equal(typeof(AUTDException), exception.GetType());
        Assert.Equal("AUTDException: Unspecified group key", exception.Message);
    }

    [Fact]
    public void GroupCheckOnlyForEnabled()
    {
        var autd = AUTDTest.CreateController();
        autd.Geometry[0].Enable = false;

        var check = new bool[autd.Geometry.NumDevices];
        Assert.True(autd.Send(new Group((dev, _) =>
        {
            check[dev.Idx] = true;
            return "uniform";
        }).Set("uniform", new Uniform(0.5).WithPhase(Math.PI))));

        Assert.False(check[0]);
        Assert.True(check[1]);

        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(0, 0);
            Assert.All(duties, d => Assert.Equal(0, d));
            Assert.All(phases, p => Assert.Equal(0, p));
        }
        {
            var (duties, phases) = autd.Link<Audit>().DutiesAndPhases(1, 0);
            Assert.All(duties, d => Assert.Equal(680, d));
            Assert.All(phases, p => Assert.Equal(2048, p));
        }
    }
}