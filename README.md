<h1 align="center">
AUTD3: Ariborne Ultrasound Tactile Display 3
</h1>

<div align="center">

![build](https://github.com/shinolab/autd3/workflows/build/badge.svg)

</div>

<div align="center">

[![release](https://img.shields.io/github/v/release/shinolab/autd3)](https://github.com/shinolab/autd3/releases/latest)
[![Crate.io version](https://img.shields.io/crates/v/autd3)](https://crates.io/crates/autd3)
[![NuGet stable version](https://img.shields.io/nuget/v/autd3sharp)](https://nuget.org/packages/AUTD3Sharp)
[![unitypackage](https://github.com/shinolab/autd3sharp/workflows/unitypackage/badge.svg)](https://github.com/shinolab/autd3sharp/releases)
[![PyPI version](https://badge.fury.io/py/pyautd3.svg)](https://badge.fury.io/py/pyautd3)
[![nim release](https://img.shields.io/github/v/tag/shinolab/autd3_nim?label=nim)](https://github.com/shinolab/autd3_nim)
[![go release](https://img.shields.io/github/v/tag/shinolab/autd3-go?label=Go)](https://github.com/shinolab/autd3-go)
[![Julia release](https://img.shields.io/github/v/tag/shinolab/AUTD3.jl?label=Julia)](https://github.com/shinolab/AUTD3.jl)
[![MATLAB release](https://img.shields.io/github/v/tag/shinolab/autd3-matlab?label=MATLAB)](https://github.com/shinolab/autd3-matlab)

</div>

<p align="center">
The Airborne Ultrasound Tactile Display (AUTD) is a midair haptic device that can remotely produce tactile sensation on a human skin surface without wearing devices.
Please see <a href="https://hapislab.org/airborne-ultrasound-tactile-display?lang=en">our laboratory homepage</a> for more details on AUTD.
This repository contains a client library to drive AUTD version 3 devices.
This cross-platform library supports Windows, macOS, and Linux (including Single Board Computer such as Raspberry Pi).
</p>

## Document

* [日本語/Japanese](https://shinolab.github.io/autd3/book/jp)
* [English](https://shinolab.github.io/autd3/book/en)
    * [API References](https://shinolab.github.io/autd3/api/)

## CAUTION

* Before using, be sure to write the latest firmware in `dist/firmware`. 
    * For more information, please see [README](/dist/firmware/README.md).

## Requirements

* If you use `link::SOEM` on Windows, install [Npcap](https://nmap.org/npcap/) with WinPcap API-compatible mode.
* If you use `link::TwinCAT` or `link::RemoteTwinCAT`, please see [how to install AUTDServer](https://shinolab.github.io/autd3/book/en/Software/Users_Manual/link.html#how-to-install-twincat).

## Build

* Pre-built binaries and header files are on the [GitHub Release page](https://github.com/shinolab/autd3/releases). 
* Or, if you want to build from the source, install CMake version 3.16 or higher and follow the instructions below.
    * Windows:
        ```
        git clone https://github.com/shinolab/autd3.git
        ```
        Then, run `build.ps1` (Visual Studio 2019 or 2022 is required) or build with CMake
    * macOS: 
        ```
        git clone https://github.com/shinolab/autd3.git
        cd autd3
        mkdir build && cd build
        cmake ..
        make
        ```

    * linux:
        ```
        git clone https://github.com/shinolab/autd3.git 
        cd autd3
        mkdir build && cd build
        cmake ..
        make
        ```

    * Some projects are disabled by default. Please enable them by switching their flags on
        * e.g., if you want to use TwinCATLink;
            ```
            cmake .. -DBUILD_LINK_TWINCAT=ON
            ```

## Example

* See `examples`

* If you are using Linux/macOS, you may need to run as root.

## CMake options list

| Option                      | default | description                          |
| -------------------------   | ------- | ------------------------------------ |
| BUILD_ALL                   | OFF     | build all basic options              |
| BUILD_DOC                   | OFF     | build doxygen documents              |
| BUILD_GAIN_HOLO             | ON      | build Holo gain                      |
| BUILD_BACKEND_CUDA          | OFF     | build CUDABackend for Holo gain      |
| BUILD_BACKEND_ARRAYFIRE     | OFF     | build ArrayFireBackend for Holo gain |
| BUILD_BACKEND_BLAS          | OFF     | build BLASBackend for Holo gain      |
| BLAS_LIB_DIR                | OFF     | BLAS lib dir                         |
| BLAS_DEPEND_LIB_DIR         | OFF     | BLAS depends lib dir                 |
| BLAS_INCLUDE_DIR            | OFF     | BLAS include dir                     |
| USE_MKL                     | OFF     | ON if use intel MKL                  |
| BUILD_MODULATION_AUDIO_FILE | OFF     | build Wav and RawPCM modulation      |
| BUILD_LINK_SOEM             | ON      | build SOEM link                      |
| BUILD_LINK_TWINCAT          | OFF     | build TwinCAT link                   |
| BUILD_LINK_REMOTE_TWINCAT   | OFF     | build RemoteTwinCAT link             |
| BUILD_LINK_EMULATOR         | OFF     | build Emulator link                  |
| BUILD_LINK_BUNDLE           | OFF     | build Bundle link                    |
| BUILD_LINK_DEBUG            | OFF     | build Debug link                     |
| BUILD_GEOMETRY_VIEWER       | OFF     | build GeometryViewer                 |
| BUILD_EXAMPLES              | ON      | build examples                       |
| BUILD_EXAMPLES_EXTRA        | ON      | build extra examples                 |
| BUILD_CAPI                  | OFF     | build C-API                          |
| ENABLE_LINT                 | OFF     | enable cpp lint                      |
| BUILD_TEST                  | OFF     | build tests                          |


## For other programming languages

* [Rust](https://github.com/shinolab/rust-autd)
* [C#](https://github.com/shinolab/autd3sharp)
* [Python](https://github.com/shinolab/pyautd)
* [Nim](https://github.com/shinolab/autd3_nim)
* [Go](https://github.com/shinolab/autd3-go)
* [Julia](https://github.com/shinolab/AUTD3.jl)
* [MATLAB](https://github.com/shinolab/autd3-matlab)

## Firmware

* The firmware codes are available at [here](https://github.com/shinolab/autd3-firmware).

## Citing

* If you use this SDK in your research please consider to include the following citation in your publications:

   * [S. Suzuki, S. Inoue, M. Fujiwara, Y. Makino and H. Shinoda, "AUTD3: Scalable Airborne Ultrasound Tactile Display," in IEEE Transactions on Haptics, doi: 10.1109/TOH.2021.3069976.](https://ieeexplore.ieee.org/document/9392322)
   * S. Inoue, Y. Makino and H. Shinoda "Scalable Architecture for Airborne Ultrasound Tactile Display", Asia Haptics 2016

## LICENSE

* See [LICENSE](./LICENSE) and [NOTICE](./NOTICE).

# Author

Shun Suzuki, 2022
