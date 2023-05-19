/*
 * File: mod.rs
 * Project: operation
 * Created Date: 08/01/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 19/05/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

mod clear;
mod flag;
mod gain;
mod info;
mod mod_delay;
mod modulation;
mod null;
mod silencer;
mod stm_focus;
mod stm_gain;
mod sync;

pub use clear::*;
pub use flag::*;
pub use gain::*;
pub use info::*;
pub use mod_delay::*;
pub use modulation::*;
pub use null::*;
pub use silencer::*;
pub use stm_focus::*;
pub use stm_gain::*;
pub use sync::*;

use crate::{DriverError, TxDatagram};

pub trait Operation {
    fn init(&mut self);
    fn pack(&mut self, tx: &mut TxDatagram) -> Result<(), DriverError>;
    fn is_finished(&self) -> bool;
}

impl Operation for Box<dyn Operation> {
    fn init(&mut self) {
        (**self).init()
    }

    fn pack(&mut self, tx: &mut TxDatagram) -> Result<(), DriverError> {
        (**self).pack(tx)
    }

    fn is_finished(&self) -> bool {
        (**self).is_finished()
    }
}
