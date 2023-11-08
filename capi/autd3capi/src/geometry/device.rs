/*
 * File: device.rs
 * Project: geometry
 * Created Date: 06/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 08/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

use autd3capi_def::{common::*, DevicePtr, GeometryPtr};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDDevice(geo: GeometryPtr, dev_idx: u32) -> DevicePtr {
    DevicePtr(&cast!(geo, Geometry)[dev_idx as usize] as *const _ as _)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDDeviceNumTransducers(dev: DevicePtr) -> u32 {
    cast!(dev, Device).num_transducers() as _
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDDeviceGetSoundSpeed(dev: DevicePtr) -> float {
    cast!(dev, Device).sound_speed
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceSetSoundSpeed(dev: DevicePtr, value: float) {
    cast_mut!(dev, Device).sound_speed = value;
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceSetSoundSpeedFromTemp(
    dev: DevicePtr,
    temp: float,
    k: float,
    r: float,
    m: float,
) {
    cast_mut!(dev, Device).set_sound_speed_from_temp_with(temp, k, r, m);
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDDeviceGetAttenuation(dev: DevicePtr) -> float {
    cast!(dev, Device).attenuation
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceSetAttenuation(dev: DevicePtr, value: float) {
    cast_mut!(dev, Device).attenuation = value;
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceCenter(dev: DevicePtr, center: *mut float) {
    let c = cast!(dev, Device).center();
    center.add(0).write(c.x);
    center.add(1).write(c.y);
    center.add(2).write(c.z);
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceTranslate(dev: DevicePtr, x: float, y: float, z: float) {
    cast_mut!(dev, Device).translate(Vector3::new(x, y, z));
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceRotate(dev: DevicePtr, w: float, i: float, j: float, k: float) {
    cast_mut!(dev, Device).rotate(UnitQuaternion::from_quaternion(Quaternion::new(w, i, j, k)));
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceAffine(
    dev: DevicePtr,
    x: float,
    y: float,
    z: float,
    w: float,
    i: float,
    j: float,
    k: float,
) {
    cast_mut!(dev, Device).affine(
        Vector3::new(x, y, z),
        UnitQuaternion::from_quaternion(Quaternion::new(w, i, j, k)),
    );
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceSetReadsFPGAInfo(dev: DevicePtr, value: bool) {
    cast_mut!(dev, Device).reads_fpga_info = value;
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceSetForceFan(dev: DevicePtr, value: bool) {
    cast_mut!(dev, Device).force_fan = value;
}

#[no_mangle]
pub unsafe extern "C" fn AUTDDeviceEnableSet(dev: DevicePtr, value: bool) {
    cast_mut!(dev, Device).enable = value;
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDDeviceEnableGet(dev: DevicePtr) -> bool {
    cast_mut!(dev, Device).enable
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        geometry::{transducer::*, *},
        tests::*,
        *,
    };

    #[test]
    fn device() {
        unsafe {
            let cnt = create_controller();
            let geo = AUTDGeometry(cnt);

            let dev = AUTDDevice(geo, 0);

            let c = 300e3;
            AUTDDeviceSetSoundSpeed(dev, c);
            assert_eq!(c, AUTDDeviceGetSoundSpeed(dev));

            AUTDDeviceSetSoundSpeedFromTemp(dev, 15.0, 1.4, 8.314_463, 28.9647e-3);
            assert_approx_eq::assert_approx_eq!(AUTDDeviceGetSoundSpeed(dev), 340295.27186788846);

            let num_transducers = AUTDDeviceNumTransducers(dev);
            assert_eq!(num_transducers, 249);

            let mut v = [0., 0., 0.];
            AUTDDeviceCenter(dev, v.as_mut_ptr());
            assert_approx_eq::assert_approx_eq!(v[0], 86.62522088353415);
            assert_approx_eq::assert_approx_eq!(v[1], 66.71325301204786);
            assert_approx_eq::assert_approx_eq!(v[2], 0.);

            assert!(AUTDDeviceEnableGet(dev));
            AUTDDeviceEnableSet(dev, false);
            assert!(!AUTDDeviceEnableGet(dev));

            AUTDControllerDelete(cnt);
        }
    }

    #[test]
    fn device_affine() {
        unsafe {
            let cnt = create_controller();
            let geo = AUTDGeometry(cnt);
            let dev = AUTDDevice(geo, 0);

            let num_trans = AUTDDeviceNumTransducers(dev) as usize;

            let mut v = vec![[0., 0., 0.]; num_trans];
            (0..num_trans).for_each(|t| {
                AUTDTransducerPosition(AUTDTransducer(dev, t as _), v[t].as_mut_ptr())
            });
            AUTDDeviceTranslate(dev, 1., 2., 3.);
            (0..num_trans).for_each(|t| {
                let mut v_new = [0., 0., 0.];
                AUTDTransducerPosition(AUTDTransducer(dev, t as _), v_new.as_mut_ptr());
                assert_approx_eq::assert_approx_eq!(v_new[0], v[t][0] + 1.);
                assert_approx_eq::assert_approx_eq!(v_new[1], v[t][1] + 2.);
                assert_approx_eq::assert_approx_eq!(v_new[2], v[t][2] + 3.);
            });

            let q = UnitQuaternion::from_axis_angle(&UnitVector3::new_normalize(Vector3::z()), 1.0);
            AUTDDeviceRotate(dev, q.w, q.i, q.j, q.k);
            (0..num_trans).for_each(|t| {
                let mut v_new = [0., 0., 0., 0.];
                AUTDTransducerRotation(AUTDTransducer(dev, t as _), v_new.as_mut_ptr());
                assert_approx_eq::assert_approx_eq!(v_new[0], q.w);
                assert_approx_eq::assert_approx_eq!(v_new[1], q.i);
                assert_approx_eq::assert_approx_eq!(v_new[2], q.j);
                assert_approx_eq::assert_approx_eq!(v_new[3], q.k);
            });

            AUTDControllerDelete(cnt);

            let cnt = create_controller();
            let geo = AUTDGeometry(cnt);
            let dev = AUTDDevice(geo, 0);

            let mut v = vec![[0., 0., 0.]; num_trans];
            (0..num_trans).for_each(|t| {
                AUTDTransducerPosition(AUTDTransducer(dev, t as _), v[t].as_mut_ptr())
            });

            let rot =
                UnitQuaternion::from_axis_angle(&UnitVector3::new_normalize(Vector3::z()), PI / 2.);
            AUTDDeviceAffine(dev, 1., 2., 3., rot.w, rot.i, rot.j, rot.k);
            (0..num_trans).for_each(|t| {
                let mut v_new = [0., 0., 0.];
                let mut q_new = [0., 0., 0., 0.];
                AUTDTransducerPosition(AUTDTransducer(dev, t as _), v_new.as_mut_ptr());
                AUTDTransducerRotation(AUTDTransducer(dev, t as _), q_new.as_mut_ptr());
                assert_approx_eq::assert_approx_eq!(v_new[0], -v[t][1] + 1.);
                assert_approx_eq::assert_approx_eq!(v_new[1], v[t][0] + 2.);
                assert_approx_eq::assert_approx_eq!(v_new[2], v[t][2] + 3.);
                assert_approx_eq::assert_approx_eq!(q_new[0], rot.w);
                assert_approx_eq::assert_approx_eq!(q_new[1], rot.i);
                assert_approx_eq::assert_approx_eq!(q_new[2], rot.j);
                assert_approx_eq::assert_approx_eq!(q_new[3], rot.k);
            });

            AUTDControllerDelete(cnt);
        }
    }
}
