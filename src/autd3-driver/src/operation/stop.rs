/*
 * File: stop.rs
 * Project: operation
 * Created Date: 01/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 14/10/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use std::collections::HashMap;

use crate::{
    common::{Amplitude, Drive},
    error::AUTDInternalError,
    fpga::AdvancedDriveDuty,
    geometry::{Device, Geometry, Transducer},
    operation::{GainControlFlags, TypeTag},
};

use super::Operation;

#[derive(Default)]
pub struct StopOp {
    remains: HashMap<usize, usize>,
}

impl<T: Transducer> Operation<T> for StopOp {
    fn pack(&mut self, device: &Device<T>, tx: &mut [u8]) -> Result<usize, AUTDInternalError> {
        tx[0] = TypeTag::Gain as u8;
        tx[1] = GainControlFlags::DUTY.bits();

        assert!(
            tx.len() >= 2 + device.num_transducers() * std::mem::size_of::<AdvancedDriveDuty>()
        );

        unsafe {
            let dst = std::slice::from_raw_parts_mut(
                tx[2..].as_mut_ptr() as *mut AdvancedDriveDuty,
                device.num_transducers(),
            );
            dst.iter_mut()
                .zip(device.iter().map(|tr| tr.cycle()))
                .for_each(|(d, c)| {
                    d.set(
                        &Drive {
                            amp: Amplitude::MIN,
                            phase: 0.,
                        },
                        c,
                    )
                });
        }

        Ok(2 + device.num_transducers() * std::mem::size_of::<AdvancedDriveDuty>())
    }

    fn required_size(&self, device: &Device<T>) -> usize {
        2 + device.num_transducers() * std::mem::size_of::<AdvancedDriveDuty>()
    }

    fn init(&mut self, geometry: &Geometry<T>) -> Result<(), AUTDInternalError> {
        self.remains = geometry.devices().map(|device| (device.idx(), 1)).collect();
        Ok(())
    }

    fn remains(&self, device: &Device<T>) -> usize {
        self.remains[&device.idx()]
    }

    fn commit(&mut self, device: &Device<T>) {
        self.remains.insert(device.idx(), 0);
    }
}

#[cfg(test)]
mod tests {

    use super::*;
    use crate::geometry::{tests::create_geometry, LegacyTransducer};

    const NUM_TRANS_IN_UNIT: usize = 249;
    const NUM_DEVICE: usize = 10;

    #[test]
    fn stop_op() {
        let geometry = create_geometry::<LegacyTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let mut tx =
            vec![0x00u8; (2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>()) * NUM_DEVICE];

        let mut op = StopOp::default();

        assert!(op.init(&geometry).is_ok());

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.required_size(dev),
                2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<AdvancedDriveDuty>()
            )
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 1));

        geometry.devices().for_each(|dev| {
            assert!(op
                .pack(
                    dev,
                    &mut tx[dev.idx() * (2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>())..]
                )
                .is_ok());
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 0));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                tx[dev.idx() * (2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>())],
                TypeTag::Gain as u8
            );
            let flag = tx[dev.idx() * (2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>()) + 1];
            assert_eq!(flag & GainControlFlags::LEGACY.bits(), 0x00);
            assert_ne!(flag & GainControlFlags::DUTY.bits(), 0x00);
            tx.iter()
                .skip((2 + NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>()) * dev.idx())
                .skip(2)
                .take(NUM_TRANS_IN_UNIT * std::mem::size_of::<u16>())
                .for_each(|&d| {
                    assert_eq!(d, 0);
                })
        });
    }
}
