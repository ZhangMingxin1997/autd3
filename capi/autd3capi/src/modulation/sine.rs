/*
 * File: sine.rs
 * Project: modulation
 * Created Date: 23/08/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 10/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

use autd3capi_def::{common::*, take_mod, ModulationPtr};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDModulationSine(freq: u32) -> ModulationPtr {
    ModulationPtr::new(Sine::new(freq as _))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDModulationSineWithSamplingFrequencyDivision(
    m: ModulationPtr,
    div: u32,
) -> ModulationPtr {
    ModulationPtr::new(take_mod!(m, Sine).with_sampling_frequency_division(div))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDModulationSineWithAmp(m: ModulationPtr, amp: float) -> ModulationPtr {
    ModulationPtr::new(take_mod!(m, Sine).with_amp(amp))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDModulationSineWithPhase(
    m: ModulationPtr,
    phase: float,
) -> ModulationPtr {
    ModulationPtr::new(take_mod!(m, Sine).with_phase(phase))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDModulationSineWithOffset(
    m: ModulationPtr,
    offset: float,
) -> ModulationPtr {
    ModulationPtr::new(take_mod!(m, Sine).with_offset(offset))
}

#[cfg(test)]
mod tests {
    use super::*;

    use crate::{modulation::*, tests::*, *};

    use autd3capi_def::{DatagramPtr, AUTD3_TRUE};

    #[test]
    fn test_sine() {
        unsafe {
            let cnt = create_controller();

            let m = AUTDModulationSine(150);
            let m = AUTDModulationSineWithAmp(m, 1.);
            let m = AUTDModulationSineWithPhase(m, 0.);
            let m = AUTDModulationSineWithOffset(m, 0.5);
            let div = 10240;
            let m = AUTDModulationSineWithSamplingFrequencyDivision(m, div);

            let m = AUTDModulationIntoDatagram(m);

            let r = AUTDControllerSend(cnt, m, DatagramPtr(std::ptr::null()), -1);
            assert_eq!(r.result, AUTD3_TRUE);

            AUTDControllerDelete(cnt);
        }
    }
}
