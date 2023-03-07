/*
 * File: point.rs
 * Project: stm
 * Created Date: 05/05/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 07/03/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 *
 */

use crate::{
    datagram::{DatagramBody, Empty, Filled, Sendable},
    geometry::{Geometry, Matrix3, Transducer, Vector3},
};

use anyhow::{Ok, Result};
use autd3_driver::*;

use super::STM;

pub struct FocusSTM {
    control_points: Vec<(Vector3, u8)>,
    pub freq_div: u32,
    pub start_idx: Option<u16>,
    pub finish_idx: Option<u16>,
}

impl FocusSTM {
    pub fn new() -> Self {
        Self {
            control_points: vec![],
            freq_div: 4096,
            start_idx: None,
            finish_idx: None,
        }
    }

    pub fn add(&mut self, point: Vector3) -> Result<()> {
        self.control_points.push((point, 0));
        Ok(())
    }

    pub fn add_with_shift(&mut self, point: Vector3, shift: u8) -> Result<()> {
        self.control_points.push((point, shift));
        Ok(())
    }

    pub fn control_points(&self) -> &[(Vector3, u8)] {
        &self.control_points
    }
}

impl<T: Transducer> DatagramBody<T> for FocusSTM {
    type O = autd3_driver::FocusSTM;

    fn operation(&mut self, geometry: &Geometry<T>) -> Result<Self::O> {
        let points = geometry
            .device_map()
            .iter()
            .scan(0, |state, tr_num| {
                let r = Some(*state);
                *state += tr_num;
                r
            })
            .map(|origin_idx| {
                let tr = &geometry[origin_idx];
                let origin = tr.position();
                let trans_inv =
                    Matrix3::from_columns(&[tr.x_direction(), tr.y_direction(), tr.z_direction()])
                        .transpose();
                self.control_points
                    .iter()
                    .map(|(p, shift)| {
                        let lp = trans_inv * (p - origin);
                        STMFocus::new(lp.x, lp.y, lp.z, *shift)
                    })
                    .collect()
            })
            .collect();
        let tr_num_min = geometry.device_map().iter().min().unwrap();

        let props = autd3_driver::FocusSTMProps {
            freq_div: self.freq_div,
            sound_speed: geometry.sound_speed,
            start_idx: self.start_idx,
            finish_idx: self.finish_idx,
        };
        Ok(Self::O::new(points, *tr_num_min, props))
    }
}

impl<T: Transducer> Sendable<T> for FocusSTM {
    type H = Empty;
    type B = Filled;
    type O = <Self as DatagramBody<T>>::O;

    fn operation(&mut self, geometry: &Geometry<T>) -> Result<Self::O> {
        <Self as DatagramBody<T>>::operation(self, geometry)
    }
}

impl STM for FocusSTM {
    fn size(&self) -> usize {
        self.control_points.len()
    }

    fn set_sampling_freq_div(&mut self, freq_div: u32) {
        self.freq_div = freq_div;
    }

    fn sampling_freq_div(&self) -> u32 {
        self.freq_div
    }
}

impl Default for FocusSTM {
    fn default() -> Self {
        Self::new()
    }
}
