/*
 * File: dynamic_link.rs
 * Project: src
 * Created Date: 06/10/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 27/10/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use autd3_driver::{error::AUTDInternalError, geometry::Geometry, link::LinkSyncBuilder};

use crate::{DynamicTransducer, L};

type LinkBuilderGen = dyn FnOnce(&Geometry<DynamicTransducer>) -> Result<Box<L>, AUTDInternalError>;

pub struct DynamicLinkBuilder {
    link_gen: Box<LinkBuilderGen>,
}

impl DynamicLinkBuilder {
    pub fn new<B: LinkSyncBuilder<DynamicTransducer> + 'static>(b: B) -> Self {
        Self {
            link_gen: Box::new(move |geometry| Ok(Box::new(b.open(geometry)?))),
        }
    }
}

impl LinkSyncBuilder<DynamicTransducer> for DynamicLinkBuilder {
    type L = Box<L>;

    fn open(self, geometry: &Geometry<DynamicTransducer>) -> Result<Self::L, AUTDInternalError> {
        (self.link_gen)(geometry)
    }
}
