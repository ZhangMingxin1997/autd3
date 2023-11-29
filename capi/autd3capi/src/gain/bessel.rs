/*
 * File: focus.rs
 * Project: gain
 * Created Date: 23/08/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 29/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use autd3capi_def::{autd3::gain::Bessel, driver::geometry::Vector3, *};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainBessel(
    x: float,
    y: float,
    z: float,
    nx: float,
    ny: float,
    nz: float,
    theta_z: float,
) -> GainPtr {
    GainPtr::new(Bessel::new(
        Vector3::new(x, y, z),
        Vector3::new(nx, ny, nz),
        theta_z,
    ))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainBesselWithIntensity(bessel: GainPtr, intensity: u8) -> GainPtr {
    GainPtr::new(take_gain!(bessel, Bessel).with_intensity(intensity))
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{gain::*, tests::*, *};

    use autd3capi_def::{DatagramPtr, AUTD3_TRUE};

    #[test]
    fn test_bessel() {
        unsafe {
            let cnt = create_controller();

            let g = AUTDGainBessel(0., 0., 0., 0., 0., 1., 1.);
            let g = AUTDGainBesselWithIntensity(g, 0xFF);
            let g = AUTDGainIntoDatagram(g);

            let r = AUTDControllerSend(cnt, g, DatagramPtr(std::ptr::null()), -1);
            assert_eq!(r.result, AUTD3_TRUE);

            AUTDControllerDelete(cnt);
        }
    }
}
