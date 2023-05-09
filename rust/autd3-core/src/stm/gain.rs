/*
 * File: gain.rs
 * Project: stm
 * Created Date: 05/05/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 09/05/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 *
 */

use crate::{
    error::AUTDInternalError,
    gain::Gain,
    geometry::{
        AdvancedPhaseTransducer, AdvancedTransducer, Geometry, LegacyTransducer, Transducer,
    },
    sendable::Sendable,
};

use autd3_driver::{GainSTMProps, Mode};

use super::STM;

#[derive(Default)]
pub struct GainSTM<'a, T: Transducer> {
    gains: Vec<Box<dyn Gain<T> + 'a>>,
    mode: Mode,
    pub freq_div: u32,
    pub start_idx: Option<u16>,
    pub finish_idx: Option<u16>,
}

impl<'a, T: Transducer> GainSTM<'a, T> {
    pub fn new() -> Self {
        Self {
            gains: vec![],
            mode: Mode::PhaseDutyFull,
            freq_div: 4096,
            start_idx: None,
            finish_idx: None,
        }
    }

    pub fn add<G: Gain<T> + 'a>(&mut self, gain: G) {
        self.gains.push(Box::new(gain));
    }
}

impl<'a, T: Transducer> STM for GainSTM<'a, T> {
    fn size(&self) -> usize {
        self.gains.len()
    }

    fn set_sampling_freq_div(&mut self, freq_div: u32) {
        self.freq_div = freq_div;
    }

    fn sampling_freq_div(&self) -> u32 {
        self.freq_div
    }
}

impl<'a> Sendable<LegacyTransducer> for GainSTM<'a, LegacyTransducer> {
    type H = autd3_driver::NullHeader;
    type B = autd3_driver::GainSTMLegacy;

    fn header_operation(&mut self) -> Result<Self::H, AUTDInternalError> {
        Ok(Default::default())
    }

    fn body_operation(
        &mut self,
        geometry: &Geometry<LegacyTransducer>,
    ) -> Result<Self::B, AUTDInternalError> {
        let drives = self
            .gains
            .iter_mut()
            .map(|g| g.calc(geometry))
            .collect::<Result<_, AUTDInternalError>>()?;
        let props = GainSTMProps {
            mode: self.mode,
            freq_div: self.freq_div,
            finish_idx: self.finish_idx,
            start_idx: self.start_idx,
        };
        Ok(Self::B::new(drives, props))
    }
}

impl<'a> Sendable<AdvancedTransducer> for GainSTM<'a, AdvancedTransducer> {
    type H = autd3_driver::NullHeader;
    type B = autd3_driver::GainSTMAdvanced;

    fn header_operation(&mut self) -> Result<Self::H, AUTDInternalError> {
        Ok(Default::default())
    }

    fn body_operation(
        &mut self,
        geometry: &Geometry<AdvancedTransducer>,
    ) -> Result<Self::B, AUTDInternalError> {
        let cycles = geometry.transducers().map(|tr| tr.cycle()).collect();
        let drives = self
            .gains
            .iter_mut()
            .map(|g| g.calc(geometry))
            .collect::<Result<_, AUTDInternalError>>()?;
        let props = GainSTMProps {
            mode: self.mode,
            freq_div: self.freq_div,
            finish_idx: self.finish_idx,
            start_idx: self.start_idx,
        };
        Ok(Self::B::new(drives, cycles, props))
    }
}

impl<'a> Sendable<AdvancedPhaseTransducer> for GainSTM<'a, AdvancedPhaseTransducer> {
    type H = autd3_driver::NullHeader;
    type B = autd3_driver::GainSTMAdvanced;

    fn header_operation(&mut self) -> Result<Self::H, AUTDInternalError> {
        Ok(Default::default())
    }

    fn body_operation(
        &mut self,
        geometry: &Geometry<AdvancedPhaseTransducer>,
    ) -> Result<Self::B, AUTDInternalError> {
        let cycles = geometry.transducers().map(|tr| tr.cycle()).collect();
        let drives = self
            .gains
            .iter_mut()
            .map(|g| g.calc(geometry))
            .collect::<Result<_, AUTDInternalError>>()?;
        let props = GainSTMProps {
            mode: Mode::PhaseDutyFull,
            freq_div: self.freq_div,
            finish_idx: self.finish_idx,
            start_idx: self.start_idx,
        };
        Ok(Self::B::new(drives, cycles, props))
    }
}
