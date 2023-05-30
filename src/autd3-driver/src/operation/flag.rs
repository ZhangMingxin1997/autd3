/*
 * File: flag.rs
 * Project: operation
 * Created Date: 08/01/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 08/05/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use crate::{FPGAControlFlags, TxDatagram};

#[derive(Default)]
pub struct ForceFan {
    pub value: bool,
}

impl ForceFan {
    pub fn pack(&mut self, tx: &mut TxDatagram) {
        tx.header_mut()
            .fpga_flag
            .set(FPGAControlFlags::FORCE_FAN, self.value);
    }
}

#[derive(Default)]
pub struct ReadsFPGAInfo {
    pub value: bool,
}

impl ReadsFPGAInfo {
    pub fn pack(&mut self, tx: &mut TxDatagram) {
        tx.header_mut()
            .fpga_flag
            .set(FPGAControlFlags::READS_FPGA_INFO, self.value);
    }
}

#[cfg(test)]
mod test {

    use super::*;

    const NUM_TRANS_IN_UNIT: usize = 249;

    #[test]
    fn force_fan() {
        let mut tx = TxDatagram::new(&[
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
        ]);

        ForceFan { value: true }.pack(&mut tx);
        assert!(tx.header().fpga_flag.contains(FPGAControlFlags::FORCE_FAN));

        ForceFan { value: false }.pack(&mut tx);
        assert!(!tx.header().fpga_flag.contains(FPGAControlFlags::FORCE_FAN));
    }

    #[test]
    fn reads_fpga_info() {
        let mut tx = TxDatagram::new(&[
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
            NUM_TRANS_IN_UNIT,
        ]);

        ReadsFPGAInfo { value: true }.pack(&mut tx);
        assert!(tx
            .header()
            .fpga_flag
            .contains(FPGAControlFlags::READS_FPGA_INFO));

        ReadsFPGAInfo { value: false }.pack(&mut tx);
        assert!(!tx
            .header()
            .fpga_flag
            .contains(FPGAControlFlags::READS_FPGA_INFO));
    }
}
