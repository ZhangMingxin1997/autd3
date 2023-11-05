/*
 * File: flag.rs
 * Project: tests
 * Created Date: 24/05/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use std::{
    io,
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc,
    },
};

use autd3::prelude::*;

pub async fn flag<T: Transducer, L: Link>(autd: &mut Controller<T, L>) -> anyhow::Result<bool> {
    autd.geometry
        .iter_mut()
        .for_each(|dev| dev.reads_fpga_info = true);

    println!("press any key to force fan...");
    let mut _s = String::new();
    io::stdin().read_line(&mut _s).unwrap();

    autd.geometry
        .iter_mut()
        .for_each(|dev| dev.force_fan = true);
    autd.send(UpdateFlags::default()).await?;

    let fin = Arc::new(AtomicBool::new(false));

    let fin2 = fin.clone();
    let fin_signal = tokio::spawn(async move {
        println!("press any key to stop checking FPGA status...");
        let mut _s = String::new();
        async_std::io::stdin().read_line(&mut _s).await.unwrap();
        fin2.store(true, Ordering::Relaxed);
    });

    let prompts = ['-', '/', '|', '\\'];
    let mut idx = 0;
    while !fin.load(Ordering::Relaxed) {
        let states = autd.fpga_info().await?;
        println!("{} FPGA Status...", prompts[idx / 1000 % prompts.len()]);
        idx += 1;
        states.iter().enumerate().for_each(|(i, state)| {
            println!("\x1b[0K[{}]: thermo = {}", i, state.is_thermal_assert());
        });
        print!("\x1b[{}A", states.len() + 1);
    }
    print!("\x1b[1F\x1b[0J");

    fin_signal.await?;

    autd.geometry.iter_mut().for_each(|dev| {
        dev.reads_fpga_info = false;
        dev.force_fan = false;
    });
    autd.send(UpdateFlags::default()).await?;

    Ok(true)
}
