/*
 * File: focus.rs
 * Project: stm
 * Created Date: 04/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use crate::{
    datagram::Datagram, defined::float, error::AUTDInternalError, geometry::*,
    operation::ControlPoint,
};

use super::STMProps;

/// FocusSTM is an STM for moving a single focal point.
///
/// The sampling timing is determined by hardware, thus the sampling time is precise.
///
/// FocusSTM has following restrictions:
/// - The maximum number of sampling points is 65536.
/// - The sampling frequency is [crate::FPGA_SUB_CLK_FREQ]/N, where `N` is a 32-bit unsigned integer and must be at least [crate::SAMPLING_FREQ_DIV_MIN]
///
#[derive(Clone)]
pub struct FocusSTM {
    control_points: Vec<ControlPoint>,
    props: STMProps,
}

impl FocusSTM {
    /// Add [ControlPoint] to FocusSTM
    pub fn add_focus<C: Into<ControlPoint>>(mut self, point: C) -> Self {
        self.control_points.push(point.into());
        self
    }

    /// Add [ControlPoint]s to FocusSTM
    pub fn add_foci_from_iter<C: Into<ControlPoint>, T: IntoIterator<Item = C>>(
        mut self,
        iter: T,
    ) -> Self {
        self.control_points
            .extend(iter.into_iter().map(|c| c.into()));
        self
    }

    /// Get [ControlPoint]s
    pub fn control_points(&self) -> &[ControlPoint] {
        &self.control_points
    }

    #[doc(hidden)]
    /// This is used only for capi.
    pub fn with_props(props: STMProps) -> Self {
        Self {
            control_points: Vec::new(),
            props,
        }
    }

    #[doc(hidden)]
    /// This is used only for capi.
    pub fn take_control_points(&mut self) -> Vec<ControlPoint> {
        std::mem::take(&mut self.control_points)
    }
}

impl<T: Transducer> Datagram<T> for FocusSTM {
    type O1 = crate::operation::FocusSTMOp;
    type O2 = crate::operation::NullOp;

    fn operation(self) -> Result<(Self::O1, Self::O2), AUTDInternalError> {
        let freq_div = self.sampling_frequency_division();
        let start_idx = self.props.start_idx;
        let finish_idx = self.props.finish_idx;
        Ok((
            Self::O1::new(self.control_points, freq_div, start_idx, finish_idx),
            Self::O2::default(),
        ))
    }
}

impl FocusSTM {
    /// constructor
    ///
    /// # Arguments
    ///
    /// * `freq` - Frequency of STM. The frequency closest to `freq` from the possible frequencies is set.
    ///
    pub fn new(freq: float) -> Self {
        Self {
            control_points: vec![],
            props: STMProps::new(freq),
        }
    }

    /// constructor
    ///
    /// # Arguments
    ///
    /// * `period` - Period. The period closest to `period` from the possible periods is set.
    ///
    pub fn with_period(period: std::time::Duration) -> Self {
        Self::new(1000000000. / period.as_nanos() as float)
    }

    /// constructor
    ///
    /// # Arguments
    ///
    /// * `freq_div` - Sampling frequency division of STM. The sampling frequency is [crate::FPGA_SUB_CLK_FREQ]/`freq_div`.
    ///
    pub fn with_sampling_frequency_division(freq_div: u32) -> Self {
        Self {
            control_points: vec![],
            props: STMProps::with_sampling_frequency_division(freq_div),
        }
    }

    /// constructor
    ///
    /// # Arguments
    ///
    /// * `freq` - Sampling frequency of STM. The sampling frequency closest to `freq` from the possible sampling frequencies is set.
    ///
    pub fn with_sampling_frequency(freq: float) -> Self {
        Self {
            control_points: vec![],
            props: STMProps::with_sampling_frequency(freq),
        }
    }

    /// constructor
    ///
    /// # Arguments
    ///
    /// * `period` - Sampling period. The sampling period closest to `period` from the possible sampling periods is set.
    ///
    pub fn with_sampling_period(period: std::time::Duration) -> Self {
        Self {
            control_points: vec![],
            props: STMProps::with_sampling_period(period),
        }
    }

    /// Set the start index of STM
    pub fn with_start_idx(self, idx: Option<u16>) -> Self {
        Self {
            props: self.props.with_start_idx(idx),
            ..self
        }
    }

    /// Set the finish index of STM
    pub fn with_finish_idx(self, idx: Option<u16>) -> Self {
        Self {
            props: self.props.with_finish_idx(idx),
            ..self
        }
    }

    pub fn start_idx(&self) -> Option<u16> {
        self.props.start_idx()
    }

    pub fn finish_idx(&self) -> Option<u16> {
        self.props.finish_idx()
    }

    #[doc(hidden)]
    /// This is used only for internal.
    pub fn size(&self) -> usize {
        self.control_points.len()
    }

    pub fn freq(&self) -> float {
        self.props.freq(self.size())
    }

    pub fn period(&self) -> std::time::Duration {
        self.props.period(self.size())
    }

    pub fn sampling_frequency(&self) -> float {
        self.props.sampling_frequency(self.size())
    }

    pub fn sampling_frequency_division(&self) -> u32 {
        self.props.sampling_frequency_division(self.size())
    }

    pub fn sampling_period(&self) -> std::time::Duration {
        self.props.sampling_period(self.size())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::fpga::FPGA_SUB_CLK_FREQ;
    use assert_approx_eq::assert_approx_eq;

    #[test]
    fn freq() {
        let stm = FocusSTM::new(1.0);
        assert_eq!(stm.freq(), 1.0);

        let stm = FocusSTM::with_sampling_frequency_division(512)
            .add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_approx_eq!(stm.freq(), FPGA_SUB_CLK_FREQ as float / 512. / 10.);

        let stm = FocusSTM::with_sampling_frequency(40e3)
            .add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_approx_eq!(stm.freq(), 40e3 / 10.);
    }

    #[test]
    fn period() {
        let stm = FocusSTM::with_period(std::time::Duration::from_millis(1));
        assert_eq!(stm.period(), std::time::Duration::from_millis(1));

        let stm = FocusSTM::with_sampling_period(std::time::Duration::from_millis(1))
            .add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_eq!(stm.period(), std::time::Duration::from_millis(10));
    }

    #[test]
    fn sampling_frequency_division() {
        let stm = FocusSTM::with_sampling_frequency_division(512);
        assert_eq!(stm.sampling_frequency_division(), 512);

        let stm = FocusSTM::new(1.0).add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_eq!(
            stm.sampling_frequency_division(),
            (FPGA_SUB_CLK_FREQ as float / 10.) as u32
        );

        let stm = FocusSTM::with_sampling_frequency(40e3);
        assert_eq!(
            stm.sampling_frequency_division(),
            (FPGA_SUB_CLK_FREQ as float / 40e3) as u32
        );
    }

    #[test]
    fn sampling_frequency() {
        let stm = FocusSTM::with_sampling_frequency(40e3);
        assert_eq!(stm.sampling_frequency(), 40e3);

        let stm = FocusSTM::with_sampling_frequency_division(512);
        assert_approx_eq!(stm.sampling_frequency(), FPGA_SUB_CLK_FREQ as float / 512.);

        let stm = FocusSTM::new(1.0).add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_approx_eq!(stm.sampling_frequency(), 1. * 10.);
    }

    #[test]
    fn sampling_period() {
        let stm = FocusSTM::with_sampling_period(std::time::Duration::from_millis(1));
        assert_eq!(stm.sampling_period(), std::time::Duration::from_millis(1));

        let stm = FocusSTM::with_period(std::time::Duration::from_millis(10))
            .add_foci_from_iter((0..10).map(|_| (Vector3::zeros(), 0)));
        assert_eq!(stm.sampling_period(), std::time::Duration::from_millis(1));
    }
}