/*
 * File: advanced.rs
 * Project: gain
 * Created Date: 06/10/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 11/10/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use std::collections::HashMap;

use crate::{
    defined::Drive,
    error::AUTDInternalError,
    fpga::{
        AdvancedDriveDuty, AdvancedDrivePhase, LegacyDrive, FPGA_SUB_CLK_FREQ_DIV,
        GAIN_STM_BUF_SIZE_MAX,
    },
    geometry::{Device, Geometry, Transducer},
    operation::TypeTag,
};

use super::{gain_stm_control_flags::GainSTMControlFlags, GainSTMMode, GainSTMOpDelegate};

pub struct GainSTMOpAdvanced {}

impl<T: Transducer> GainSTMOpDelegate<T> for GainSTMOpAdvanced {
    #[allow(clippy::too_many_arguments)]
    fn pack(
        drives: &[HashMap<usize, Vec<Drive>>],
        remains: &HashMap<usize, usize>,
        sent_map: &mut HashMap<usize, usize>,
        mode: GainSTMMode,
        freq_div: u32,
        start_idx: Option<u16>,
        finish_idx: Option<u16>,
        device: &Device<T>,
        tx: &mut [u8],
    ) -> Result<usize, AUTDInternalError> {
        tx[0] = TypeTag::GainSTM as u8;

        let sent = sent_map[&device.idx()];
        let mut offset =
            std::mem::size_of::<TypeTag>() + std::mem::size_of::<GainSTMControlFlags>();
        if sent == 0 {
            offset += std::mem::size_of::<GainSTMMode>()
             + std::mem::size_of::<u32>() // freq_div
             + std::mem::size_of::<u16>() // start idx
             + std::mem::size_of::<u16>(); // finish idx
        }
        assert!(tx.len() >= offset + device.num_transducers() * 2);

        let mut f = GainSTMControlFlags::NONE;
        f.set(GainSTMControlFlags::STM_BEGIN, sent == 0);
        f.set(GainSTMControlFlags::STM_END, remains[&device.idx()] == 1);

        if sent == 0 {
            let mode = mode as u16;
            tx[2] = (mode & 0xFF) as u8;
            tx[3] = (mode >> 8) as u8;

            let freq_div = freq_div * FPGA_SUB_CLK_FREQ_DIV as u32;
            tx[4] = (freq_div & 0xFF) as u8;
            tx[5] = ((freq_div >> 8) & 0xFF) as u8;
            tx[6] = ((freq_div >> 16) & 0xFF) as u8;
            tx[7] = ((freq_div >> 24) & 0xFF) as u8;

            f.set(GainSTMControlFlags::USE_START_IDX, start_idx.is_some());
            let start_idx = start_idx.unwrap_or(0);
            tx[8] = (start_idx & 0xFF) as u8;
            tx[9] = (start_idx >> 8) as u8;

            f.set(GainSTMControlFlags::USE_FINISH_IDX, finish_idx.is_some());
            let finish_idx = finish_idx.unwrap_or(0);
            tx[10] = (finish_idx & 0xFF) as u8;
            tx[11] = (finish_idx >> 8) as u8;
        }

        match mode {
            GainSTMMode::PhaseDutyFull => {
                let d = &drives[sent / 2][&device.idx()];

                if sent % 2 == 0 {
                    unsafe {
                        let dst = std::slice::from_raw_parts_mut(
                            tx[offset..].as_mut_ptr() as *mut AdvancedDrivePhase,
                            d.len(),
                        );
                        dst.iter_mut()
                            .zip(d.iter())
                            .zip(device.iter())
                            .for_each(|((d, s), tr)| d.set(s, tr.cycle()));
                    }
                } else {
                    f.set(GainSTMControlFlags::DUTY, true);

                    unsafe {
                        let dst = std::slice::from_raw_parts_mut(
                            tx[offset..].as_mut_ptr() as *mut AdvancedDriveDuty,
                            d.len(),
                        );
                        dst.iter_mut()
                            .zip(d.iter())
                            .zip(device.iter())
                            .for_each(|((d, s), tr)| d.set(s, tr.cycle()));
                    }
                }

                sent_map.insert(device.idx(), sent + 1);
            }
            GainSTMMode::PhaseFull => {
                let d = &drives[sent][&device.idx()];

                unsafe {
                    let dst = std::slice::from_raw_parts_mut(
                        tx[offset..].as_mut_ptr() as *mut AdvancedDrivePhase,
                        d.len(),
                    );
                    dst.iter_mut()
                        .zip(d.iter())
                        .zip(device.iter())
                        .for_each(|((d, s), tr)| d.set(s, tr.cycle()));
                }

                sent_map.insert(device.idx(), sent + 1);
            }
            GainSTMMode::PhaseHalf => unreachable!(),
        }
        tx[1] = f.bits();

        if sent == 0 {
            Ok(std::mem::size_of::<TypeTag>()
             + std::mem::size_of::<GainSTMControlFlags>()
             + std::mem::size_of::<GainSTMMode>()
             + std::mem::size_of::<u32>() // freq_div
             + std::mem::size_of::<u16>() // start idx
             + std::mem::size_of::<u16>() // finish idx
             +device.num_transducers() * std::mem::size_of::<AdvancedDrivePhase>())
        } else {
            Ok(std::mem::size_of::<TypeTag>()
                + std::mem::size_of::<GainSTMControlFlags>()
                + device.num_transducers() * std::mem::size_of::<u16>())
        }
    }

    fn init(
        n: usize,
        mode: GainSTMMode,
        geometry: &Geometry<T>,
    ) -> Result<HashMap<usize, usize>, AUTDInternalError> {
        if !(2..=GAIN_STM_BUF_SIZE_MAX).contains(&n) {
            return Err(AUTDInternalError::GainSTMSizeOutOfRange(n));
        }

        match mode {
            GainSTMMode::PhaseDutyFull => Ok(geometry
                .devices()
                .map(|device| (device.idx(), 2 * n))
                .collect()),
            GainSTMMode::PhaseFull => {
                Ok(geometry.devices().map(|device| (device.idx(), n)).collect())
            }
            GainSTMMode::PhaseHalf => Err(AUTDInternalError::GainSTMModeNotSupported(mode)),
        }
    }

    fn commit(
        drives: &[HashMap<usize, Vec<Drive>>],
        remains: &mut HashMap<usize, usize>,
        sent: &HashMap<usize, usize>,
        mode: GainSTMMode,
        device: &Device<T>,
    ) {
        match mode {
            GainSTMMode::PhaseDutyFull => {
                remains.insert(device.idx(), 2 * drives.len() - sent[&device.idx()])
            }
            GainSTMMode::PhaseFull => {
                remains.insert(device.idx(), drives.len() - sent[&device.idx()])
            }
            GainSTMMode::PhaseHalf => unreachable!(),
        };
    }

    fn required_size(sent: &HashMap<usize, usize>, device: &Device<T>) -> usize {
        if sent[&device.idx()] == 0 {
            std::mem::size_of::<TypeTag>()
                 + std::mem::size_of::<GainSTMControlFlags>()
                 + std::mem::size_of::<GainSTMMode>()
                 + std::mem::size_of::<u32>() // freq_div
                 + std::mem::size_of::<u16>() // start idx
                 + std::mem::size_of::<u16>() // finish idx
                 + device.num_transducers() * std::mem::size_of::<LegacyDrive>()
        } else {
            std::mem::size_of::<TypeTag>()
                + std::mem::size_of::<GainSTMControlFlags>()
                + device.num_transducers() * std::mem::size_of::<LegacyDrive>()
        }
    }
}

#[cfg(test)]
mod tests {
    use rand::prelude::*;

    use super::*;
    use crate::{
        defined::PI,
        derive::prelude::Operation,
        fpga::{GAIN_STM_BUF_SIZE_MAX, SAMPLING_FREQ_DIV_MAX, SAMPLING_FREQ_DIV_MIN},
        geometry::{tests::create_geometry, AdvancedTransducer},
        operation::{
            tests::{NullGain, TestGain},
            GainSTMOp,
        },
    };

    const NUM_TRANS_IN_UNIT: usize = 249;
    const NUM_DEVICE: usize = 10;

    #[test]
    fn gain_stm_advanced_phase_duty_full_op() {
        const GAIN_STM_SIZE: usize = 2;
        const FRAME_SIZE: usize = 12 + NUM_TRANS_IN_UNIT * 2;

        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let mut tx = vec![0x00u8; FRAME_SIZE * NUM_DEVICE];

        let mut rng = rand::thread_rng();

        let gain_data: Vec<HashMap<usize, Vec<Drive>>> = (0..GAIN_STM_SIZE)
            .map(|_| {
                geometry
                    .devices()
                    .map(|dev| {
                        (
                            dev.idx(),
                            (0..dev.num_transducers())
                                .map(|_| Drive {
                                    amp: rng.gen_range(0.0..1.0),
                                    phase: rng.gen_range(0.0..2.0 * PI),
                                })
                                .collect(),
                        )
                    })
                    .collect()
            })
            .collect();
        let gains: Vec<TestGain> = (0..GAIN_STM_SIZE)
            .map(|i| TestGain {
                data: gain_data[i].clone(),
            })
            .collect();

        let freq_div: u32 = rng.gen_range(SAMPLING_FREQ_DIV_MIN..SAMPLING_FREQ_DIV_MAX);
        let mut op =
            GainSTMOp::<_, _>::new(gains, GainSTMMode::PhaseDutyFull, freq_div, None, None);
        let freq_div = freq_div * FPGA_SUB_CLK_FREQ_DIV as u32;

        assert!(op.init(&geometry).is_ok());

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 2 * GAIN_STM_SIZE));

        // First frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 12 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(12 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 2 * GAIN_STM_SIZE - 1));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 2],
                ((GainSTMMode::PhaseDutyFull as u16) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 3],
                ((GainSTMMode::PhaseDutyFull as u16) >> 8) as u8
            );

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 4], (freq_div & 0xFF) as u8);
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 5],
                ((freq_div >> 8) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 6],
                ((freq_div >> 16) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 7],
                ((freq_div >> 24) & 0xFF) as u8
            );

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 8], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 9], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 10], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 11], 0x00);

            tx[FRAME_SIZE * dev.idx() + 12..]
                .chunks(std::mem::size_of::<AdvancedDrivePhase>())
                .zip(gain_data[0][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let phase = AdvancedDrivePhase::to_phase(g, tr.cycle());
                    assert_eq!(d[0], (phase & 0xFF) as u8);
                    assert_eq!(d[1], (phase >> 8) as u8);
                })
        });

        // Second frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 2 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(2 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 2 * GAIN_STM_SIZE - 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            tx[FRAME_SIZE * dev.idx() + 2..]
                .chunks(std::mem::size_of::<AdvancedDriveDuty>())
                .zip(gain_data[0][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let duty = AdvancedDriveDuty::to_duty(g, tr.cycle());
                    assert_eq!(d[0], (duty & 0xFF) as u8);
                    assert_eq!(d[1], (duty >> 8) as u8);
                })
        });

        // Third frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 2 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(2 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 2 * GAIN_STM_SIZE - 3));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            tx[FRAME_SIZE * dev.idx() + 2..]
                .chunks(std::mem::size_of::<AdvancedDrivePhase>())
                .zip(gain_data[1][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let phase = AdvancedDrivePhase::to_phase(g, tr.cycle());
                    assert_eq!(d[0], (phase & 0xFF) as u8);
                    assert_eq!(d[1], (phase >> 8) as u8);
                })
        });

        // Final frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 2 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(2 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 0));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            tx[FRAME_SIZE * dev.idx() + 2..]
                .chunks(std::mem::size_of::<AdvancedDriveDuty>())
                .zip(gain_data[1][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let duty = AdvancedDriveDuty::to_duty(g, tr.cycle());
                    assert_eq!(d[0], (duty & 0xFF) as u8);
                    assert_eq!(d[1], (duty >> 8) as u8);
                })
        });
    }

    #[test]
    fn gain_stm_advanced_phase_full_op() {
        const GAIN_STM_SIZE: usize = 3;
        const FRAME_SIZE: usize = 12 + NUM_TRANS_IN_UNIT * 2;

        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let mut tx = vec![0x00u8; FRAME_SIZE * NUM_DEVICE];

        let mut rng = rand::thread_rng();

        let gain_data: Vec<HashMap<usize, Vec<Drive>>> = (0..GAIN_STM_SIZE)
            .map(|_| {
                geometry
                    .devices()
                    .map(|dev| {
                        (
                            dev.idx(),
                            (0..dev.num_transducers())
                                .map(|_| Drive {
                                    amp: rng.gen_range(0.0..1.0),
                                    phase: rng.gen_range(0.0..2.0 * PI),
                                })
                                .collect(),
                        )
                    })
                    .collect()
            })
            .collect();
        let gains: Vec<TestGain> = (0..GAIN_STM_SIZE)
            .map(|i| TestGain {
                data: gain_data[i].clone(),
            })
            .collect();

        let freq_div: u32 = rng.gen_range(SAMPLING_FREQ_DIV_MIN..SAMPLING_FREQ_DIV_MAX);
        let mut op = GainSTMOp::<_, _>::new(gains, GainSTMMode::PhaseFull, freq_div, None, None);
        let freq_div = freq_div * FPGA_SUB_CLK_FREQ_DIV as u32;

        assert!(op.init(&geometry).is_ok());

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), GAIN_STM_SIZE));

        // First frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 12 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(12 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), GAIN_STM_SIZE - 1));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 2],
                ((GainSTMMode::PhaseFull as u16) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 3],
                ((GainSTMMode::PhaseFull as u16) >> 8) as u8
            );

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 4], (freq_div & 0xFF) as u8);
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 5],
                ((freq_div >> 8) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 6],
                ((freq_div >> 16) & 0xFF) as u8
            );
            assert_eq!(
                tx[dev.idx() * FRAME_SIZE + 7],
                ((freq_div >> 24) & 0xFF) as u8
            );

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 8], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 9], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 10], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 11], 0x00);

            tx[FRAME_SIZE * dev.idx() + 12..]
                .chunks(std::mem::size_of::<AdvancedDrivePhase>())
                .zip(gain_data[0][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let phase = AdvancedDrivePhase::to_phase(g, tr.cycle());
                    assert_eq!(d[0], (phase & 0xFF) as u8);
                    assert_eq!(d[1], (phase >> 8) as u8);
                })
        });

        // Second frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 2 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(2 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), GAIN_STM_SIZE - 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            tx[FRAME_SIZE * dev.idx() + 2..]
                .chunks(std::mem::size_of::<AdvancedDrivePhase>())
                .zip(gain_data[1][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let phase = AdvancedDrivePhase::to_phase(g, tr.cycle());
                    assert_eq!(d[0], (phase & 0xFF) as u8);
                    assert_eq!(d[1], (phase >> 8) as u8);
                })
        });

        // Final frame
        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.required_size(dev), 2 + NUM_TRANS_IN_UNIT * 2));

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(2 + NUM_TRANS_IN_UNIT * 2)
            );
            op.commit(dev);
        });

        geometry
            .devices()
            .for_each(|dev| assert_eq!(op.remains(dev), 0));

        geometry.devices().for_each(|dev| {
            assert_eq!(tx[dev.idx() * FRAME_SIZE], TypeTag::GainSTM as u8);
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::LEGACY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::DUTY.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::STM_BEGIN.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::STM_END.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            tx[FRAME_SIZE * dev.idx() + 2..]
                .chunks(std::mem::size_of::<AdvancedDrivePhase>())
                .zip(gain_data[2][&dev.idx()].iter())
                .zip(dev.iter())
                .for_each(|((d, g), tr)| {
                    let phase = AdvancedDrivePhase::to_phase(g, tr.cycle());
                    assert_eq!(d[0], (phase & 0xFF) as u8);
                    assert_eq!(d[1], (phase >> 8) as u8);
                })
        });
    }

    #[test]
    fn gain_stm_advanced_phase_half_op() {
        const GAIN_STM_SIZE: usize = 2;

        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let mut rng = rand::thread_rng();

        let gain_data: Vec<HashMap<usize, Vec<Drive>>> = (0..GAIN_STM_SIZE)
            .map(|_| {
                geometry
                    .devices()
                    .map(|dev| {
                        (
                            dev.idx(),
                            (0..dev.num_transducers())
                                .map(|_| Drive {
                                    amp: rng.gen_range(0.0..1.0),
                                    phase: rng.gen_range(0.0..2.0 * PI),
                                })
                                .collect(),
                        )
                    })
                    .collect()
            })
            .collect();
        let gains: Vec<TestGain> = (0..GAIN_STM_SIZE)
            .map(|i| TestGain {
                data: gain_data[i].clone(),
            })
            .collect();

        let freq_div: u32 = rng.gen_range(SAMPLING_FREQ_DIV_MIN..SAMPLING_FREQ_DIV_MAX);

        let mut op = GainSTMOp::<_, _>::new(gains, GainSTMMode::PhaseHalf, freq_div, None, None);

        assert!(op.init(&geometry).is_err());
    }

    #[test]
    fn gain_stm_advanced_op_idx() {
        const FRAME_SIZE: usize = 12 + NUM_TRANS_IN_UNIT * 2;

        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let mut tx = vec![0x00u8; FRAME_SIZE * NUM_DEVICE];

        let mut rng = rand::thread_rng();

        let start_idx = rng.gen_range(0..2_u16);
        let finish_idx = rng.gen_range(0..2_u16);

        let mut rng = rand::thread_rng();

        let gain_data: Vec<HashMap<usize, Vec<Drive>>> = (0..2)
            .map(|_| {
                geometry
                    .devices()
                    .map(|dev| {
                        (
                            dev.idx(),
                            (0..dev.num_transducers())
                                .map(|_| Drive {
                                    amp: rng.gen_range(0.0..1.0),
                                    phase: rng.gen_range(0.0..2.0 * PI),
                                })
                                .collect(),
                        )
                    })
                    .collect()
            })
            .collect();
        let gains: Vec<TestGain> = (0..2)
            .map(|i| TestGain {
                data: gain_data[i].clone(),
            })
            .collect();

        let mut op = GainSTMOp::<_, _>::new(
            gains.clone(),
            GainSTMMode::PhaseDutyFull,
            SAMPLING_FREQ_DIV_MIN,
            Some(start_idx),
            Some(finish_idx),
        );
        assert!(op.init(&geometry).is_ok());

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(FRAME_SIZE)
            );
            op.commit(dev);
        });

        geometry.devices().for_each(|dev| {
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_ne!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 8], (start_idx & 0xFF) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 9], (start_idx >> 8) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 10], (finish_idx & 0xFF) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 11], (finish_idx >> 8) as u8);
        });

        let mut op = GainSTMOp::<_, _>::new(
            gains.clone(),
            GainSTMMode::PhaseDutyFull,
            SAMPLING_FREQ_DIV_MIN,
            Some(start_idx),
            None,
        );
        assert!(op.init(&geometry).is_ok());

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(FRAME_SIZE)
            );
            op.commit(dev);
        });

        geometry.devices().for_each(|dev| {
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_ne!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_eq!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 8], (start_idx & 0xFF) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 9], (start_idx >> 8) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 10], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 11], 0x00);
        });

        let mut op = GainSTMOp::<_, _>::new(
            gains.clone(),
            GainSTMMode::PhaseDutyFull,
            SAMPLING_FREQ_DIV_MIN,
            None,
            Some(finish_idx),
        );
        assert!(op.init(&geometry).is_ok());

        geometry.devices().for_each(|dev| {
            assert_eq!(
                op.pack(dev, &mut tx[dev.idx() * FRAME_SIZE..]),
                Ok(FRAME_SIZE)
            );
            op.commit(dev);
        });

        geometry.devices().for_each(|dev| {
            let flag = tx[dev.idx() * FRAME_SIZE + 1];
            assert_eq!(flag & GainSTMControlFlags::USE_START_IDX.bits(), 0x00);
            assert_ne!(flag & GainSTMControlFlags::USE_FINISH_IDX.bits(), 0x00);

            assert_eq!(tx[dev.idx() * FRAME_SIZE + 8], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 9], 0x00);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 10], (finish_idx & 0xFF) as u8);
            assert_eq!(tx[dev.idx() * FRAME_SIZE + 11], (finish_idx >> 8) as u8);
        });
    }

    #[test]
    fn gain_stm_advanced_op_buffer_out_of_range() {
        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let test = |n: usize| {
            let gains: Vec<NullGain> = (0..n).map(|_| NullGain {}).collect();

            let mut op = GainSTMOp::<_, _>::new(
                gains,
                GainSTMMode::PhaseDutyFull,
                SAMPLING_FREQ_DIV_MIN,
                None,
                None,
            );
            op.init(&geometry)
        };

        assert_eq!(test(1), Err(AUTDInternalError::GainSTMSizeOutOfRange(1)));
        assert_eq!(test(2), Ok(()));
        assert_eq!(test(GAIN_STM_BUF_SIZE_MAX), Ok(()));
        assert_eq!(
            test(GAIN_STM_BUF_SIZE_MAX + 1),
            Err(AUTDInternalError::GainSTMSizeOutOfRange(
                GAIN_STM_BUF_SIZE_MAX + 1
            ))
        );
    }

    #[test]
    fn gain_stm_advanced_op_freq_div_out_of_range() {
        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let test = |d: u32| {
            let gains: Vec<NullGain> = (0..2).map(|_| NullGain {}).collect();

            let mut op = GainSTMOp::<_, _>::new(gains, GainSTMMode::PhaseDutyFull, d, None, None);
            op.init(&geometry)
        };

        assert_eq!(
            test(SAMPLING_FREQ_DIV_MIN - 1),
            Err(AUTDInternalError::GainSTMFreqDivOutOfRange(
                SAMPLING_FREQ_DIV_MIN - 1
            ))
        );
        assert_eq!(test(SAMPLING_FREQ_DIV_MIN), Ok(()));
        assert_eq!(test(SAMPLING_FREQ_DIV_MAX), Ok(()));
        assert_eq!(
            test(SAMPLING_FREQ_DIV_MAX + 1),
            Err(AUTDInternalError::GainSTMFreqDivOutOfRange(
                SAMPLING_FREQ_DIV_MAX + 1
            ))
        );
    }

    #[test]
    fn gain_stm_advenced_op_stm_idx_out_of_range() {
        let geometry = create_geometry::<AdvancedTransducer>(NUM_DEVICE, NUM_TRANS_IN_UNIT);

        let test = |n: usize, start_idx: Option<u16>, finish_idx: Option<u16>| {
            let mut op = GainSTMOp::new(
                (0..n).map(|_| NullGain {}).collect(),
                GainSTMMode::PhaseDutyFull,
                SAMPLING_FREQ_DIV_MIN,
                start_idx,
                finish_idx,
            );
            op.init(&geometry)
        };

        assert_eq!(test(10, Some(0), Some(0)), Ok(()));
        assert_eq!(test(10, Some(9), Some(0)), Ok(()));
        assert_eq!(
            test(10, Some(10), Some(0)),
            Err(AUTDInternalError::STMStartIndexOutOfRange)
        );

        assert_eq!(test(10, Some(0), Some(0)), Ok(()));
        assert_eq!(test(10, Some(0), Some(9)), Ok(()));
        assert_eq!(
            test(10, Some(0), Some(10)),
            Err(AUTDInternalError::STMFinishIndexOutOfRange)
        );
    }
}
