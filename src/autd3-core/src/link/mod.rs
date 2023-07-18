/*
 * File: link.rs
 * Project: src
 * Created Date: 27/04/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 18/07/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
 *
 */

mod logger;

pub use logger::get_logger;
pub use logger::get_logger_with_custom_func;

use std::time::Duration;

use crate::error::AUTDInternalError;
use crate::geometry::Geometry;
use crate::geometry::Transducer;

use autd3_driver::{RxDatagram, TxDatagram};

/// Link is a interface to the AUTD device
pub trait Link<T: Transducer>: Send {
    /// Open link
    fn open(&mut self, geometry: &Geometry<T>) -> Result<(), AUTDInternalError>;
    /// Close link
    fn close(&mut self) -> Result<(), AUTDInternalError>;
    /// Send data to devices
    fn send(&mut self, tx: &TxDatagram) -> Result<bool, AUTDInternalError>;
    /// Receive data from devices
    fn receive(&mut self, rx: &mut RxDatagram) -> Result<bool, AUTDInternalError>;
    /// Check if link is open
    fn is_open(&self) -> bool;
    /// Get timeout
    fn timeout(&self) -> Duration;
    /// Send and receive data
    fn send_receive(
        &mut self,
        tx: &TxDatagram,
        rx: &mut RxDatagram,
        timeout: Duration,
    ) -> Result<bool, AUTDInternalError> {
        if !self.send(tx)? {
            return Ok(false);
        }
        if timeout.is_zero() {
            return self.receive(rx);
        }
        self.wait_msg_processed(tx.header().msg_id, rx, timeout)
    }

    /// Wait until message is processed
    fn wait_msg_processed(
        &mut self,
        msg_id: u8,
        rx: &mut RxDatagram,
        timeout: Duration,
    ) -> Result<bool, AUTDInternalError> {
        let start = std::time::Instant::now();
        loop {
            std::thread::sleep(std::time::Duration::from_millis(1));
            if self.receive(rx)? && rx.is_msg_processed(msg_id) {
                return Ok(true);
            }
            if start.elapsed() > timeout {
                return Ok(false);
            }
        }
    }
}

impl<T: Transducer> Link<T> for Box<dyn Link<T>> {
    fn open(&mut self, geometry: &Geometry<T>) -> Result<(), AUTDInternalError> {
        self.as_mut().open(geometry)
    }

    fn close(&mut self) -> Result<(), AUTDInternalError> {
        self.as_mut().close()
    }

    fn send(&mut self, tx: &TxDatagram) -> Result<bool, AUTDInternalError> {
        self.as_mut().send(tx)
    }

    fn receive(&mut self, rx: &mut RxDatagram) -> Result<bool, AUTDInternalError> {
        self.as_mut().receive(rx)
    }

    fn is_open(&self) -> bool {
        self.as_ref().is_open()
    }

    fn timeout(&self) -> Duration {
        self.as_ref().timeout()
    }
}
