/*
 * File: gs.rs
 * Project: src
 * Created Date: 24/08/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

use std::rc::Rc;

use autd3capi_def::{
    common::*, create_holo, holo::*, take_gain, BackendPtr, ConstraintPtr, GainPtr,
};
#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainHoloGS(
    backend: BackendPtr,
    points: *const float,
    amps: *const float,
    size: u64,
) -> GainPtr {
    create_holo!(GS, NalgebraBackend, backend, points, amps, size)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainHoloGSWithConstraint(
    holo: GainPtr,
    constraint: ConstraintPtr,
) -> GainPtr {
    GainPtr::new(
        take_gain!(holo, GS<NalgebraBackend>).with_constraint(*Box::from_raw(constraint.0 as _)),
    )
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainHoloGSWithRepeat(holo: GainPtr, repeat: u32) -> GainPtr {
    GainPtr::new(take_gain!(holo, GS<NalgebraBackend>).with_repeat(repeat as _))
}

#[cfg(test)]
mod tests {
    use std::ffi::c_char;

    use super::*;
    use crate::{constraint::*, nalgebra_backend::*, tests::*};

    use autd3capi::{gain::*, *};
    use autd3capi_def::{DatagramPtr, AUTD3_TRUE};

    #[test]
    fn test_holo_gs() {
        unsafe {
            let cnt = create_controller();

            let backend = AUTDNalgebraBackend();

            let size = 2;
            let points = [10., 20., 30., 40., 50., 60.];
            let amps = vec![1.; size];

            let holo = AUTDGainHoloGS(backend, points.as_ptr(), amps.as_ptr(), size as _);
            let constraint = AUTDGainHoloDotCareConstraint();
            let holo = AUTDGainHoloGSWithConstraint(holo, constraint);
            let constraint = AUTDGainHoloNormalizeConstraint();
            let holo = AUTDGainHoloGSWithConstraint(holo, constraint);
            let constraint = AUTDGainHoloUniformConstraint(1.);
            let holo = AUTDGainHoloGSWithConstraint(holo, constraint);
            let constraint = AUTDGainHoloClampConstraint(0., 1.);
            let holo = AUTDGainHoloGSWithConstraint(holo, constraint);

            let holo = AUTDGainHoloGSWithRepeat(holo, 100);

            let holo = AUTDGainIntoDatagram(holo);

            let mut err = vec![c_char::default(); 256];
            assert_eq!(
                AUTDSend(
                    cnt,
                    autd3capi_def::TransMode::Legacy,
                    DatagramPtr(std::ptr::null()),
                    holo,
                    -1,
                    err.as_mut_ptr(),
                ),
                AUTD3_TRUE
            );

            AUTDDeleteNalgebraBackend(backend);
            AUTDFreeController(cnt);
        }
    }
}
