/*
 * File: emit_intensity.rs
 * Project: common
 * Created Date: 11/11/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 25/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use crate::defined::{float, PI};

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(C)]
pub struct EmitIntensity {
    value: u8,
}

impl EmitIntensity {
    pub const MAX: EmitIntensity = EmitIntensity { value: 255 };
    pub const MIN: EmitIntensity = EmitIntensity { value: 0 };
    pub const DEFAULT_CORRECTED_ALPHA: float = 0.803;

    pub fn new(value: u8) -> Self {
        Self { value }
    }

    pub fn new_with_correction(value: u8) -> Self {
        Self::new_with_correction_alpha(value, Self::DEFAULT_CORRECTED_ALPHA)
    }

    pub fn new_with_correction_alpha(value: u8, alpha: float) -> Self {
        Self {
            value: ((value as float / 255.).powf(1. / alpha).asin() / PI * 510.0).round() as u8,
        }
    }

    pub fn value(&self) -> u8 {
        self.value
    }
}

impl From<u8> for EmitIntensity {
    fn from(v: u8) -> Self {
        Self::new(v)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::{
        collections::hash_map::DefaultHasher,
        hash::{Hash, Hasher},
    };

    #[test]
    fn test_new() {
        for i in 0x00..=0xFF {
            let intensity = EmitIntensity::new(i);
            assert_eq!(intensity.value(), i);
        }
    }

    #[test]
    fn test_new_with_correction() {
        for i in 0..=0xFF {
            let intensity = EmitIntensity::new_with_correction(i);
            assert_eq!(
                intensity.value(),
                ((i as float / 255.)
                    .powf(1. / EmitIntensity::DEFAULT_CORRECTED_ALPHA)
                    .asin()
                    / PI
                    * 510.0)
                    .round() as u8
            );
        }
    }

    #[test]
    fn test_clone() {
        let intensity = EmitIntensity::new(0);
        assert_eq!(intensity.value(), intensity.clone().value());
    }

    #[test]
    fn test_debug() {
        let intensity = EmitIntensity::new(0);
        assert_eq!(format!("{:?}", intensity), "EmitIntensity { value: 0 }");
    }

    #[test]
    fn test_ord() {
        let intensity1 = EmitIntensity::new(0);
        let intensity2 = EmitIntensity::new(1);
        assert!(intensity1 < intensity2);
        assert_eq!(intensity1.min(intensity2), intensity1);
    }

    #[test]
    fn hash() {
        let intensity = EmitIntensity::new(0);
        let mut s = DefaultHasher::new();
        assert_eq!(intensity.hash(&mut s), 0.hash(&mut s));
        s.finish();
    }
}