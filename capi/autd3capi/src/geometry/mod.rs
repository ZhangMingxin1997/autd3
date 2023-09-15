/*
 * File: mod.rs
 * Project: geometry
 * Created Date: 24/08/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 08/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

pub mod device;
pub mod transducer;

use autd3capi_def::{common::*, ControllerPtr, GeometryPtr};

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGetGeometry(cnt: ControllerPtr) -> GeometryPtr {
    GeometryPtr(cast!(cnt.0, Cnt).geometry() as *const _ as _)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDGeometryNumDevices(geo: GeometryPtr) -> u32 {
    cast!(geo.0, Geo).num_devices() as _
}

#[cfg(test)]
mod tests {
    use super::*;

    use crate::{tests::*, *};

    #[test]
    fn test_geometry() {
        unsafe {
            let cnt = create_controller();
            let geo = AUTDGetGeometry(cnt);

            let num_devices = AUTDGeometryNumDevices(geo) as usize;
            assert_eq!(num_devices, 2);

            AUTDFreeController(cnt);
        }
    }
}