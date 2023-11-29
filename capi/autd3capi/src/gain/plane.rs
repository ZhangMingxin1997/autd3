/*
 * File: plane.rs
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

use autd3capi_def::{autd3::gain::Plane, driver::geometry::Vector3, *};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainPlane(nx: float, ny: float, nz: float) -> GainPtr {
    GainPtr::new(Plane::new(Vector3::new(nx, ny, nz)))
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGainPlaneWithIntensity(plane: GainPtr, intensity: u8) -> GainPtr {
    GainPtr::new(take_gain!(plane, Plane).with_intensity(intensity))
}

#[cfg(test)]
mod tests {
    use super::*;

    use crate::{gain::*, tests::*, *};

    use autd3capi_def::{DatagramPtr, AUTD3_TRUE};

    #[test]
    fn test_plane() {
        unsafe {
            let cnt = create_controller();

            let g = AUTDGainPlane(0., 0., 1.);
            let g = AUTDGainPlaneWithIntensity(g, 0xFF);
            let g = AUTDGainIntoDatagram(g);

            let r = AUTDControllerSend(cnt, g, DatagramPtr(std::ptr::null()), -1);
            assert_eq!(r.result, AUTD3_TRUE);

            AUTDControllerDelete(cnt);
        }
    }
}
