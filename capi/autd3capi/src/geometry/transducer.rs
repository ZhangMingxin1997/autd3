/*
 * File: transducer.rs
 * Project: devmetry
 * Created Date: 24/08/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

use autd3capi_def::{common::*, DevicePtr, TransducerPtr};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDTransducer(dev: DevicePtr, tr_idx: u32) -> TransducerPtr {
    TransducerPtr(&cast!(dev.0, Device)[tr_idx as usize] as *const _ as _)
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerPosition(tr: TransducerPtr, pos: *mut float) {
    let p = cast!(tr.0, Transducer).position();
    pos.add(0).write(p.x);
    pos.add(1).write(p.y);
    pos.add(2).write(p.z);
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerRotation(tr: TransducerPtr, rot: *mut float) {
    let r = cast!(tr.0, Transducer).rotation();
    rot.add(0).write(r.w);
    rot.add(1).write(r.i);
    rot.add(2).write(r.j);
    rot.add(3).write(r.k);
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerDirectionX(tr: TransducerPtr, dir: *mut float) {
    let d = cast!(tr.0, Transducer).x_direction();
    dir.add(0).write(d.x);
    dir.add(1).write(d.y);
    dir.add(2).write(d.z);
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerDirectionY(tr: TransducerPtr, dir: *mut float) {
    let d = cast!(tr.0, Transducer).y_direction();
    dir.add(0).write(d.x);
    dir.add(1).write(d.y);
    dir.add(2).write(d.z);
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerDirectionZ(tr: TransducerPtr, dir: *mut float) {
    let d = cast!(tr.0, Transducer).z_direction();
    dir.add(0).write(d.x);
    dir.add(1).write(d.y);
    dir.add(2).write(d.z);
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDTransducerWavelength(tr: TransducerPtr, sound_speed: float) -> float {
    cast!(tr.0, Transducer).wavelength(sound_speed)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDTransducerModDelayGet(tr: TransducerPtr) -> u16 {
    cast!(tr.0, Transducer).mod_delay()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerModDelaySet(tr: TransducerPtr, delay: u16) {
    cast_mut!(tr.0, Transducer).set_mod_delay(delay)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDTransducerAmpFilterGet(tr: TransducerPtr) -> float {
    cast!(tr.0, Transducer).amp_filter()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerAmpFilterSet(tr: TransducerPtr, value: float) {
    cast_mut!(tr.0, Transducer).set_amp_filter(value)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDTransducerPhaseFilterGet(tr: TransducerPtr) -> float {
    cast!(tr.0, Transducer).phase_filter()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDTransducerPhaseFilterSet(tr: TransducerPtr, value: float) {
    cast_mut!(tr.0, Transducer).set_phase_filter(value)
}

#[cfg(test)]
mod tests {

    use super::*;

    use crate::{
        geometry::{device::*, *},
        tests::*,
        *,
    };

    #[test]
    fn test_transducer() {
        unsafe {
            let cnt = create_controller();
            let geo = AUTDGeometry(cnt);

            let dev = AUTDDevice(geo, 0);

            let tr = AUTDTransducer(dev, 0);

            assert_approx_eq::assert_approx_eq!(AUTDTransducerWavelength(tr, 340.), 340.0 / 40e3);

            let mut v = [0., 0., 0.];
            AUTDTransducerPosition(tr, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 0.);
            assert_approx_eq::assert_approx_eq!(v[1], 0.);
            assert_approx_eq::assert_approx_eq!(v[2], 0.);

            let mut v = [0., 0., 0., 0.];
            AUTDTransducerRotation(tr, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 1.);
            assert_approx_eq::assert_approx_eq!(v[1], 0.);
            assert_approx_eq::assert_approx_eq!(v[2], 0.);
            assert_approx_eq::assert_approx_eq!(v[3], 0.);

            AUTDTransducerDirectionX(tr, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 1.);
            assert_approx_eq::assert_approx_eq!(v[1], 0.);
            assert_approx_eq::assert_approx_eq!(v[2], 0.);
            AUTDTransducerDirectionY(tr, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 0.);
            assert_approx_eq::assert_approx_eq!(v[1], 1.);
            assert_approx_eq::assert_approx_eq!(v[2], 0.);
            AUTDTransducerDirectionZ(tr, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 0.);
            assert_approx_eq::assert_approx_eq!(v[1], 0.);
            assert_approx_eq::assert_approx_eq!(v[2], 1.);

            let delay = 0xFFFF;
            AUTDTransducerModDelaySet(tr, delay);
            assert_eq!(delay, AUTDTransducerModDelayGet(tr));

            AUTDControllerDelete(cnt);
        }
    }
}
