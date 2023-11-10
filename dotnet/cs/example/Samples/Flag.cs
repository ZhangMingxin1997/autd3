﻿/*
 * File: Flag.cs
 * Project: Samples
 * Created Date: 13/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

using AUTD3Sharp;

namespace Samples;

internal static class FlagTest
{
    public static async Task Test(Controller autd)
    {
        foreach (var dev in autd.Geometry)
        {
            dev.ReadsFPGAInfo = true;
            dev.ForceFan = true;
        }

        Console.WriteLine("press any key to run fan...");
        Console.ReadKey(true);

        await autd.SendAsync(new UpdateFlags());

        var fin = false;
        var th = Task.Run(() =>
        {
            Console.WriteLine("press any key stop checking FPGA status...");
            Console.ReadKey(true);
            fin = true;
        });

        var prompts = new[] { '-', '/', '|', '\\' };
        var promptsIdx = 0;
        while (!fin)
        {
            var states = await autd.FPGAInfoAsync();
            Console.WriteLine($"{prompts[promptsIdx++ / 1000 % prompts.Length]} FPGA Status...");
            Console.WriteLine(string.Join("\n", states));
            Console.Write($"\x1b[{states.Length + 1}A");
        }

        th.Wait();

        foreach (var dev in autd.Geometry)
        {
            dev.ReadsFPGAInfo = false;
            dev.ForceFan = false;
        }

        await autd.SendAsync(new UpdateFlags());
    }
}
