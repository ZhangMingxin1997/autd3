/*
 * File: group.rs
 * Project: tests
 * Created Date: 15/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use autd3::prelude::*;

pub async fn group<L: Link>(
    autd: &mut Controller<L>,
) -> anyhow::Result<bool> {
    let center = autd.geometry.center() + Vector3::new(0., 0., 150.0 * MILLIMETER);

    autd.group(|dev| match dev.idx() {
        0 => Some("null"),
        1 => Some("focus"),
        _ => None,
    })
    .set("null", (Static::new(), Null::new()))?
    .set("focus", (Sine::new(150), Focus::new(center)))?
    .send()
    .await?;

    Ok(true)
}
