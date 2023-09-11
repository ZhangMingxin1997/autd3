/*
 * File: focus.rs
 * Project: gain
 * Created Date: 28/04/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 12/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
 *
 */

use std::collections::HashMap;

use autd3_driver::{
    derive::prelude::*,
    geometry::{Device, Vector3},
};

use autd3_derive::Gain;

/// Gain to produce single focal point
#[derive(Gain, Clone, Copy)]
pub struct Focus {
    amp: float,
    pos: Vector3,
}

impl Focus {
    /// constructor
    ///
    /// # Arguments
    ///
    /// * `pos` - position of focal point
    ///
    pub fn new(pos: Vector3) -> Self {
        Self { pos, amp: 1.0 }
    }

    /// set amplitude
    ///
    /// # Arguments
    ///
    /// * `amp` - normalized amp (from 0 to 1)
    ///
    pub fn with_amp(self, amp: float) -> Self {
        Self { amp, ..self }
    }

    pub fn amp(&self) -> float {
        self.amp
    }

    pub fn pos(&self) -> Vector3 {
        self.pos
    }
}

impl<T: Transducer> Gain<T> for Focus {
    fn calc(
        &self,
        devices: &[&Device<T>],
        filter: GainFilter,
    ) -> Result<HashMap<usize, Vec<Drive>>, AUTDInternalError> {
        Ok(Self::transform(devices, filter, |dev, tr| {
            let phase = tr.align_phase_at(self.pos, dev.sound_speed);
            Drive {
                phase,
                amp: self.amp,
            }
        }))
    }
}

#[cfg(test)]
mod tests {
    use autd3_driver::{
        acoustics::{propagate, Complex, Sphere},
        geometry::{IntoDevice, LegacyTransducer},
    };

    use super::*;

    use crate::{autd3_device::AUTD3, tests::random_vector3};

    #[test]
    fn test_focus() {
        let device: Device<LegacyTransducer> =
            AUTD3::new(Vector3::zeros(), Vector3::zeros()).into_device(0);

        let f = random_vector3(-500.0..500.0, -500.0..500.0, 50.0..500.0);
        let d = Focus::new(f).calc(&[&device], GainFilter::All).unwrap();
        assert_eq!(d[&0].len(), device.num_transducers());
        d[&0].iter().for_each(|d| assert_eq!(d.amp, 1.0));
        d[&0].iter().zip(device.iter()).for_each(|(d, tr)| {
            assert_approx_eq::assert_approx_eq!(
                (propagate::<Sphere>(
                    tr.position(),
                    &tr.z_direction(),
                    0.,
                    tr.wavenumber(device.sound_speed),
                    &f,
                ) * Complex::new(0., d.phase).exp())
                .arg(),
                0.
            )
        });

        let f = random_vector3(-500.0..500.0, -500.0..500.0, 50.0..500.0);
        let d = Focus::new(f)
            .with_amp(0.5)
            .calc(&[&device], GainFilter::All)
            .unwrap();
        assert_eq!(d[&0].len(), device.num_transducers());
        d[&0].iter().for_each(|d| assert_eq!(d.amp, 0.5));
        d[&0].iter().zip(device.iter()).for_each(|(d, tr)| {
            assert_approx_eq::assert_approx_eq!(
                (propagate::<Sphere>(
                    tr.position(),
                    &tr.z_direction(),
                    0.,
                    tr.wavenumber(device.sound_speed),
                    &f,
                ) * Complex::new(0., d.phase).exp())
                .arg(),
                0.
            )
        });
    }
}
