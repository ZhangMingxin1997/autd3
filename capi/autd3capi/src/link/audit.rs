/*
 * File: audit.rs
 * Project: link
 * Created Date: 18/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 06/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(clippy::missing_safety_doc)]

use autd3capi_def::{
    common::{autd3::link::audit::*, *},
    LinkBuilderPtr, LinkPtr,
};
use std::time::Duration;

#[repr(C)]
pub struct LinkAuditBuilderPtr(pub ConstPtr);

impl LinkAuditBuilderPtr {
    pub fn new(builder: AuditBuilder) -> Self {
        Self(Box::into_raw(Box::new(builder)) as _)
    }
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAudit() -> LinkAuditBuilderPtr {
    LinkAuditBuilderPtr::new(Audit::builder())
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditWithTimeout(
    audit: LinkAuditBuilderPtr,
    timeout_ns: u64,
) -> LinkAuditBuilderPtr {
    LinkAuditBuilderPtr::new(
        Box::from_raw(audit.0 as *mut AuditBuilder).with_timeout(Duration::from_nanos(timeout_ns)),
    )
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditIntoBuilder(audit: LinkAuditBuilderPtr) -> LinkBuilderPtr {
    LinkBuilderPtr::new(Box::from_raw(audit.0 as *mut AuditBuilder).blocking())
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditIsOpen(audit: LinkPtr) -> bool {
    cast!(audit.0, Box<AuditSync>).inner.is_open()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditTimeoutNs(audit: LinkPtr) -> u64 {
    cast!(audit.0, Box<AuditSync>).inner.timeout().as_nanos() as _
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditLastTimeoutNs(audit: LinkPtr) -> u64 {
    cast!(audit.0, Box<AuditSync>)
        .inner
        .last_timeout()
        .as_nanos() as _
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditDown(audit: LinkPtr) {
    cast_mut!(audit.0, Box<AuditSync>).inner.down()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditUp(audit: LinkPtr) {
    cast_mut!(audit.0, Box<AuditSync>).inner.up()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditBreakDown(audit: LinkPtr) {
    cast_mut!(audit.0, Box<AuditSync>).inner.break_down()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditRepair(audit: LinkPtr) {
    cast_mut!(audit.0, Box<AuditSync>).inner.repair()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditCpuUpdate(audit: LinkPtr, idx: u32) {
    cast_mut!(audit.0, Box<AuditSync>).inner[idx as usize].update()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditCpuIdx(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize].idx() as _
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditCpuNumTransducers(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize].num_transducers() as _
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditCpuAck(audit: LinkPtr, idx: u32) -> u8 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize].ack()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditCpuRxData(audit: LinkPtr, idx: u32) -> u8 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize].rx_data()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditCpuFpgaFlags(audit: LinkPtr, idx: u32) -> u8 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga_flags()
        .bits()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaAssertThermalSensor(audit: LinkPtr, idx: u32) {
    cast_mut!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga_mut()
        .assert_thermal_sensor()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaDeassertThermalSensor(audit: LinkPtr, idx: u32) {
    cast_mut!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga_mut()
        .deassert_thermal_sensor()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaIsForceFan(audit: LinkPtr, idx: u32) -> bool {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .is_force_fan()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaIsStmMode(audit: LinkPtr, idx: u32) -> bool {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .is_stm_mode()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaIsStmGainMode(audit: LinkPtr, idx: u32) -> bool {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .is_stm_gain_mode()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaSilencerStep(audit: LinkPtr, idx: u32) -> u16 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .silencer_step()
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaModDelays(audit: LinkPtr, idx: u32, delay: *mut u16) {
    std::ptr::copy_nonoverlapping(
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .mod_delays()
            .as_ptr(),
        delay,
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .mod_delays()
            .len(),
    )
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaDutyFilters(audit: LinkPtr, idx: u32, filters: *mut i16) {
    std::ptr::copy_nonoverlapping(
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .duty_filters()
            .as_ptr(),
        filters,
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .duty_filters()
            .len(),
    )
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaPhaseFilters(
    audit: LinkPtr,
    idx: u32,
    filters: *mut i16,
) {
    std::ptr::copy_nonoverlapping(
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .phase_filters()
            .as_ptr(),
        filters,
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .phase_filters()
            .len(),
    )
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaStmFrequencyDivision(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .stm_frequency_division()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaStmCycle(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .stm_cycle() as _
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaSoundSpeed(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .sound_speed()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaStmStartIdx(audit: LinkPtr, idx: u32) -> i32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .stm_start_idx()
        .map_or(-1, |v| v as _)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaStmFinishIdx(audit: LinkPtr, idx: u32) -> i32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .stm_finish_idx()
        .map_or(-1, |v| v as _)
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaModulationFrequencyDivision(
    audit: LinkPtr,
    idx: u32,
) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .modulation_frequency_division()
}

#[no_mangle]
#[must_use]
pub unsafe extern "C" fn AUTDLinkAuditFpgaModulationCycle(audit: LinkPtr, idx: u32) -> u32 {
    cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .modulation_cycle() as _
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaModulation(audit: LinkPtr, idx: u32, data: *mut u8) {
    std::ptr::copy_nonoverlapping(
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .modulation()
            .as_ptr(),
        data,
        cast!(audit.0, Box<AuditSync>).inner[idx as usize]
            .fpga()
            .modulation()
            .len(),
    )
}

#[no_mangle]
pub unsafe extern "C" fn AUTDLinkAuditFpgaDutiesAndPhases(
    audit: LinkPtr,
    idx: u32,
    stm_idx: u32,
    duties: *mut u16,
    phases: *mut u16,
) {
    let dp = cast!(audit.0, Box<AuditSync>).inner[idx as usize]
        .fpga()
        .duties_and_phases(stm_idx as _);
    let d = dp.iter().map(|v| v.0).collect::<Vec<_>>();
    let p = dp.iter().map(|v| v.1).collect::<Vec<_>>();
    std::ptr::copy_nonoverlapping(d.as_ptr(), duties, d.len());
    std::ptr::copy_nonoverlapping(p.as_ptr(), phases, p.len());
}

#[cfg(test)]
mod tests {
    use driver::fpga::FPGAControlFlags;

    use crate::{
        gain::{null::AUTDGainNull, AUTDGainIntoDatagram},
        geometry::{
            device::{AUTDDevice, AUTDDeviceSetForceFan},
            AUTDGeometry,
        },
        link::AUTDLinkGet,
        *,
    };

    use super::*;

    unsafe fn create_controller() -> ControllerPtr {
        let builder = AUTDControllerBuilder();
        let builder = AUTDControllerBuilderAddDevice(builder, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        let builder = AUTDControllerBuilderAddDevice(builder, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

        let audit = AUTDLinkAudit();
        let audit = AUTDLinkAuditWithTimeout(audit, 0);
        let audit = AUTDLinkAuditIntoBuilder(audit);

        let mut err = vec![c_char::default(); 256];
        let cnt = AUTDControllerOpenWith(builder, audit, err.as_mut_ptr());
        assert_ne!(cnt.0, NULL);
        cnt
    }

    #[test]
    fn test_link_debug() {
        unsafe {
            let link = AUTDLinkAudit();
            let _ = AUTDLinkAuditWithTimeout(link, 10);
        }
    }

    #[test]
    fn test_link_cpu_idx() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(AUTDLinkAuditCpuIdx(link, 0), 0);
            assert_eq!(AUTDLinkAuditCpuIdx(link, 1), 1);
        }
    }

    #[test]
    fn test_link_cpu_num_transducers() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(AUTDLinkAuditCpuNumTransducers(link, 0), 249);
            assert_eq!(AUTDLinkAuditCpuNumTransducers(link, 1), 249);
        }
    }

    #[test]
    fn test_link_cpu_ack() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(AUTDLinkAuditCpuAck(link, 0), 3);
            assert_eq!(AUTDLinkAuditCpuAck(link, 1), 3);

            let update = AUTDDatagramUpdateFlags();
            let mut err = vec![c_char::default(); 256];
            let _ = AUTDControllerSend(
                cnt,
                update,
                DatagramPtr(std::ptr::null()),
                -1,
                err.as_mut_ptr(),
            );

            assert_eq!(AUTDLinkAuditCpuAck(link, 0), 4);
            assert_eq!(AUTDLinkAuditCpuAck(link, 1), 4);
        }
    }

    #[test]
    fn test_link_cpu_rx_data() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(AUTDLinkAuditCpuRxData(link, 0), 0);
            assert_eq!(AUTDLinkAuditCpuRxData(link, 1), 0);
        }
    }

    #[test]
    fn test_link_cpu_fpga_flags() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(
                AUTDLinkAuditCpuFpgaFlags(link, 0),
                FPGAControlFlags::NONE.bits()
            );
            assert_eq!(
                AUTDLinkAuditCpuFpgaFlags(link, 1),
                FPGAControlFlags::NONE.bits()
            );

            AUTDDeviceSetForceFan(AUTDDevice(AUTDGeometry(cnt), 0), true);
            AUTDDeviceSetForceFan(AUTDDevice(AUTDGeometry(cnt), 1), true);

            let update = AUTDDatagramUpdateFlags();
            let mut err = vec![c_char::default(); 256];
            let _ = AUTDControllerSend(
                cnt,
                update,
                DatagramPtr(std::ptr::null()),
                -1,
                err.as_mut_ptr(),
            );

            assert_eq!(
                AUTDLinkAuditCpuFpgaFlags(link, 0),
                FPGAControlFlags::FORCE_FAN.bits()
            );
            assert_eq!(
                AUTDLinkAuditCpuFpgaFlags(link, 1),
                FPGAControlFlags::FORCE_FAN.bits()
            );
        }
    }

    #[test]
    fn test_fpga_thermal_sensor() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            AUTDLinkAuditFpgaAssertThermalSensor(link, 0);
        }
    }

    #[test]
    fn test_fpga_is_legacy_mode() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert!(!AUTDLinkAuditFpgaIsLegacyMode(link, 0));
            assert!(!AUTDLinkAuditFpgaIsLegacyMode(link, 1));

            let gain = AUTDGainNull();
            let gain = AUTDGainIntoDatagram(gain);
            let mut err = vec![c_char::default(); 256];
            let _ = AUTDControllerSend(
                cnt,
                gain,
                DatagramPtr(std::ptr::null()),
                -1,
                err.as_mut_ptr(),
            );

            assert!(AUTDLinkAuditFpgaIsLegacyMode(link, 0));
            assert!(AUTDLinkAuditFpgaIsLegacyMode(link, 1));
        }
    }

    #[test]
    fn test_fpga_is_force_fan() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert!(!AUTDLinkAuditFpgaIsForceFan(link, 0));
            assert!(!AUTDLinkAuditFpgaIsForceFan(link, 1));

            AUTDDeviceSetForceFan(AUTDDevice(AUTDGeometry(cnt), 0), true);
            AUTDDeviceSetForceFan(AUTDDevice(AUTDGeometry(cnt), 1), true);

            let update = AUTDDatagramUpdateFlags();
            let mut err = vec![c_char::default(); 256];
            let _ = AUTDControllerSend(
                cnt,
                update,
                DatagramPtr(std::ptr::null()),
                -1,
                err.as_mut_ptr(),
            );

            assert!(AUTDLinkAuditFpgaIsForceFan(link, 0));
            assert!(AUTDLinkAuditFpgaIsForceFan(link, 1));
        }
    }

    #[test]
    fn test_fpga_is_stm_mode() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert!(!AUTDLinkAuditFpgaIsStmMode(link, 0));
            assert!(!AUTDLinkAuditFpgaIsStmMode(link, 1));
        }
    }

    #[test]
    fn test_fpga_is_stm_gain_mode() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert!(!AUTDLinkAuditFpgaIsStmGainMode(link, 0));
            assert!(!AUTDLinkAuditFpgaIsStmGainMode(link, 1));
        }
    }

    #[test]
    fn test_fpga_silencer_step() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            assert_eq!(AUTDLinkAuditFpgaSilencerStep(link, 0), 10);
            assert_eq!(AUTDLinkAuditFpgaSilencerStep(link, 1), 10);
        }
    }

    #[test]
    fn test_fpga_cycles() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditCpuNumTransducers(link, i);

                let mut cycles = vec![0; n as usize];
                AUTDLinkAuditFpgaCycles(link, i, cycles.as_mut_ptr());

                cycles.iter().for_each(|&v| assert_eq!(v, 4096));
            })
        }
    }

    #[test]
    fn test_fpga_mod_delays() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditCpuNumTransducers(link, i);

                let mut delays = vec![0; n as usize];
                AUTDLinkAuditFpgaModDelays(link, i, delays.as_mut_ptr());

                delays.iter().for_each(|&v| assert_eq!(v, 0));
            })
        }
    }

    #[test]
    fn test_fpga_duty_filter() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditCpuNumTransducers(link, i);

                let mut filters = vec![0; n as usize];
                AUTDLinkAuditFpgaDutyFilters(link, i, filters.as_mut_ptr());

                filters.iter().for_each(|&v| assert_eq!(v, 0));
            })
        }
    }

    #[test]
    fn test_fpga_phase_filter() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditCpuNumTransducers(link, i);

                let mut filters = vec![0; n as usize];
                AUTDLinkAuditFpgaPhaseFilters(link, i, filters.as_mut_ptr());

                filters.iter().for_each(|&v| assert_eq!(v, 0));
            })
        }
    }

    #[test]
    fn test_fpga_stm_freq_div() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaStmFrequencyDivision(link, i), 0);
            })
        }
    }

    #[test]
    fn test_fpga_stm_cycle() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaStmCycle(link, i), 1);
            })
        }
    }

    #[test]
    fn test_fpga_stm_sound_speed() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaSoundSpeed(link, i), 0);
            })
        }
    }

    #[test]
    fn test_fpga_stm_start_idx() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaStmStartIdx(link, i), -1);
            })
        }
    }

    #[test]
    fn test_fpga_stm_finish_idx() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaStmFinishIdx(link, i), -1);
            })
        }
    }

    #[test]
    fn test_fpga_modulation_freq_div() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaModulationFrequencyDivision(link, i), 40960);
            })
        }
    }

    #[test]
    fn test_fpga_modulation_cycle() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                assert_eq!(AUTDLinkAuditFpgaModulationCycle(link, i), 2);
            })
        }
    }

    #[test]
    fn test_fpga_modulation() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditFpgaModulationCycle(link, i);
                let mut data = vec![0; n as usize];
                AUTDLinkAuditFpgaModulation(link, i, data.as_mut_ptr());
                data.iter().for_each(|&v| assert_eq!(v, 0));
            })
        }
    }

    #[test]
    fn test_fpga_duties_and_phases() {
        unsafe {
            let cnt = create_controller();
            let link = AUTDLinkGet(cnt);

            (0..2).for_each(|i| {
                let n = AUTDLinkAuditCpuNumTransducers(link, i);

                let mut duties = vec![0; n as usize];
                let mut phases = vec![0; n as usize];
                AUTDLinkAuditFpgaDutiesAndPhases(
                    link,
                    i,
                    0,
                    duties.as_mut_ptr(),
                    phases.as_mut_ptr(),
                );
                duties.iter().for_each(|&v| assert_eq!(v, 0));
                phases.iter().for_each(|&v| assert_eq!(v, 0));
            })
        }
    }
}
