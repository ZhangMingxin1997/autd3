/*
 * File: null.rs
 * Project: backend
 * Created Date: 17/07/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 05/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

use crate::{Backend, Config};

use autd3::driver::defined::float;

/// Backend with no plotting
pub struct NullBackend {}

pub struct NullPlotConfig {}

impl Config for NullPlotConfig {
    fn print_progress(&self) -> bool {
        false
    }
}

impl Backend for NullBackend {
    type PlotConfig = NullPlotConfig;

    fn new() -> Self {
        Self {}
    }

    fn initialize(&mut self) -> Result<(), crate::error::VisualizerError> {
        Ok(())
    }

    fn plot_1d(
        _observe_points: Vec<float>,
        _acoustic_pressures: Vec<autd3::driver::acoustics::Complex>,
        _resolution: float,
        _x_label: &str,
        _config: Self::PlotConfig,
    ) -> Result<(), crate::error::VisualizerError> {
        Err(crate::error::VisualizerError::NotSupported)
    }

    fn plot_2d(
        _observe_x: Vec<float>,
        _observe_y: Vec<float>,
        _acoustic_pressures: Vec<autd3::driver::acoustics::Complex>,
        _resolution: float,
        _x_label: &str,
        _y_label: &str,
        _config: Self::PlotConfig,
    ) -> Result<(), crate::error::VisualizerError> {
        Err(crate::error::VisualizerError::NotSupported)
    }

    fn plot_modulation(
        _modulation: Vec<float>,
        _config: Self::PlotConfig,
    ) -> Result<(), crate::error::VisualizerError> {
        Err(crate::error::VisualizerError::NotSupported)
    }

    fn plot_phase<T: autd3::driver::geometry::Transducer>(
        _config: Self::PlotConfig,
        _geometry: &autd3::geometry::Geometry<T>,
        _phases: Vec<float>,
    ) -> Result<(), crate::error::VisualizerError> {
        Err(crate::error::VisualizerError::NotSupported)
    }
}
