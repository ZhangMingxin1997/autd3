/*
 * File: gspat.rs
 * Project: linear_synthesis
 * Created Date: 29/05/2021
 * Author: Shun Suzuki
 * -----
 * Last Modified: 08/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2021 Shun Suzuki. All rights reserved.
 *
 */

use std::{collections::HashMap, sync::Arc};

use crate::{
    constraint::Constraint, helper::generate_result, impl_holo, Complex, LinAlgBackend, Trans,
};
use autd3_derive::Gain;

use autd3_driver::{
    derive::prelude::*,
    geometry::{Geometry, Vector3},
};

/// Gain to produce multiple foci with GS-PAT algorithm
///
/// Reference
/// * Plasencia, Diego Martinez, et al. "GS-PAT: high-speed multi-point sound-fields for phased arrays of transducers." ACM Transactions on Graphics (TOG) 39.4 (2020): 138-1.
#[derive(Gain)]
pub struct GSPAT<B: LinAlgBackend + 'static> {
    foci: Vec<Vector3>,
    amps: Vec<float>,
    repeat: usize,
    constraint: Constraint,
    backend: Arc<B>,
}

impl_holo!(B, GSPAT<B>);

impl<B: LinAlgBackend + 'static> GSPAT<B> {
    pub fn new(backend: Arc<B>) -> Self {
        Self {
            foci: vec![],
            amps: vec![],
            repeat: 100,
            backend,
            constraint: Constraint::Normalize,
        }
    }

    pub fn with_repeat(self, repeat: usize) -> Self {
        Self { repeat, ..self }
    }

    pub fn repeat(&self) -> usize {
        self.repeat
    }
}

impl<B: LinAlgBackend> Gain for GSPAT<B> {
    fn calc(
        &self,
        geometry: &Geometry,
        filter: GainFilter,
    ) -> Result<HashMap<usize, Vec<Drive>>, AUTDInternalError> {
        let g = self
            .backend
            .generate_propagation_matrix(geometry, &self.foci, &filter)?;

        let m = self.backend.cols_c(&g)?;
        let n = self.foci.len();

        let mut q = self.backend.alloc_zeros_cv(m)?;

        let amps = self.backend.from_slice_cv(&self.amps)?;

        let mut b = self.backend.alloc_cm(m, n)?;
        self.backend.gen_back_prop(m, n, &g, &amps, &mut b)?;

        let mut r = self.backend.alloc_zeros_cm(n, n)?;
        self.backend.gemm_c(
            Trans::NoTrans,
            Trans::NoTrans,
            Complex::new(1., 0.),
            &g,
            &b,
            Complex::new(0., 0.),
            &mut r,
        )?;

        let mut p = self.backend.clone_cv(&amps)?;
        let mut gamma = self.backend.clone_cv(&amps)?;
        self.backend.gemv_c(
            Trans::NoTrans,
            Complex::new(1., 0.),
            &r,
            &p,
            Complex::new(0., 0.),
            &mut gamma,
        )?;
        for _ in 0..self.repeat {
            self.backend.scaled_to_cv(&gamma, &amps, &mut p)?;
            self.backend.gemv_c(
                Trans::NoTrans,
                Complex::new(1., 0.),
                &r,
                &p,
                Complex::new(0., 0.),
                &mut gamma,
            )?;
        }

        let mut tmp = self.backend.clone_cv(&gamma)?;
        self.backend.reciprocal_assign_c(&mut tmp)?;
        self.backend.normalize_assign_cv(&mut gamma)?;
        self.backend.hadamard_product_assign_cv(&tmp, &mut p)?;
        self.backend.hadamard_product_assign_cv(&amps, &mut p)?;
        self.backend.hadamard_product_assign_cv(&amps, &mut p)?;

        self.backend.gemv_c(
            Trans::NoTrans,
            Complex::new(1., 0.),
            &b,
            &p,
            Complex::new(0., 0.),
            &mut q,
        )?;

        generate_result(
            geometry,
            self.backend.to_host_cv(q)?,
            &self.constraint,
            filter,
        )
    }
}
