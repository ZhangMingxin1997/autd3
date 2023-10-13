/*
 * File: main.rs
 * Project: autd-server
 * Created Date: 29/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 14/10/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 *
 */

#![allow(non_snake_case)]

mod log_formatter;

use log_formatter::LogFormatter;

use autd3_driver::link::Link;
use autd3_link_twincat::TwinCAT;
use autd3_protobuf::*;

use clap::Parser;

use tokio::{runtime::Runtime, sync::mpsc};
use tonic::transport::Server;

use std::sync::RwLock;

#[derive(Parser)]
struct Arg {
    /// Client port
    #[clap(short = 'p', long = "port")]
    port: u16,
    /// Timeout in ms
    #[clap(short = 't', long = "timeout", default_value = "0")]
    timeout: u64,
}
struct LightweightTwinCATServer {
    twincat: RwLock<TwinCAT>,
}

impl Drop for LightweightTwinCATServer {
    fn drop(&mut self) {
        tracing::info!("Shutting down server...");
        let _ = Link::close(&mut *self.twincat.write().unwrap());
        tracing::info!("Shutting down server...done");
    }
}

fn main_() -> anyhow::Result<()> {
    let args = Arg::parse();

    let port = args.port;
    let timeout = std::time::Duration::from_millis(args.timeout);

    let f = move || -> autd3_link_twincat::local::twincat_link::TwinCATBuilder {
        autd3_link_twincat::TwinCAT::builder().with_timeout(timeout)
    };
    let (tx, mut rx) = mpsc::channel(1);
    ctrlc::set_handler(move || {
        let rt = Runtime::new().expect("failed to obtain a new Runtime object");
        rt.block_on(tx.send(())).unwrap();
    })
    .expect("Error setting Ctrl-C handler");

    let addr = format!("0.0.0.0:{}", port).parse()?;
    tracing::info!("Waiting for client connection on {}", addr);
    let rt = Runtime::new().expect("failed to obtain a new Runtime object");

    let server = autd3_protobuf::LightweightServer::new(f);
    let server_future = Server::builder()
        .add_service(ecat_light_server::EcatLightServer::new(server))
        .serve_with_shutdown(addr, async {
            let _ = rx.recv().await;
        });
    rt.block_on(server_future)?;

    Ok(())
}

fn main() {
    tracing_subscriber::fmt().event_format(LogFormatter).init();

    match main_() {
        Ok(_) => {}
        Err(e) => {
            tracing::error!("{}", e);
            std::process::exit(-1);
        }
    }
}
