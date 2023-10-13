# SOEM

[SOEM](https://github.com/OpenEtherCATsociety/SOEM) is an open source EtherCAT master library developed by volunteers.
Unlike TwinCAT, it runs on a regular Windows PC, so real-time performance is not guaranteed.
Therefore, it is recommended to use TwinCAT.
SOEM should be used only if there is no other choice or only during development.
On the other hand, SOEM is cross-platform and easy to install.

If you are using Windows, install [npcap](https://nmap.org/npcap/) in **WinPcap API compatible mode**.
If you are using Linux/macOS, no special preparation is required.

> NOTE: If you are using `SOEM`, be aware that it takes about 10-20 seconds after opening `Controller` for the EtherCAT slaves to synchronize with each other.
> This period is subject to individual differences and changes depending on the synchronization signal/transmission cycle.
> During this period, the ultrasound synchronization between devices is not guaranteed.

[[_TOC_]]

## SOEM link API

### Interface name

You can specify the network interface on which the AUTD3 device is connected with `with_ifname`.

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::SOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_ifname("")
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

autd3::link::SOEM::builder()
	.with_ifname("")
```

```cs
SOEM.Builder()
    .WithIfname("")
```

```python
from pyautd3.link.soem import SOEM

SOEM.builder()\
    .with_ifname("")
```

By default, it is blank, and if it is blank, the network interface to which the AUTD3 device is connected is automatically selected.

### Callback when error occurs

You can set a callback with `with_on_err` function when an error occurs.

The interval of error status check is specified by `with_state_check_interval` function. (Default is $\SI{100}{ms}$.)

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::SOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_state_check_interval(std::time::Duration::from_millis(100))
    .with_on_err(|msg| {
            eprintln!("Unrecoverable error occurred: {msg}");
        })
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

void on_err(const char* msg) {
  std::cerr << msg;
}

autd3::link::SOEM::builder()
    .with_state_check_interval(std::chrono::milliseconds(100))
    .with_on_err(&on_err)
```

```cs
var onErr = new SOEM.OnErrCallbackDelegate((string msg) =>
{
    Console.WriteLine(msg);
});

SOEM.Builder()
    .WithStateCheckInterval(TimeSpan.FromMilliseconds(100))
    .WithOnErr(onErr)
```

```python
from pyautd3.link.soem import SOEM, OnErrFunc
from datetime import timedelta

def on_err(msg: ctypes.c_char_p):
    print(msg.decode("utf-8"), end="")

on_err_func = OnErrFunc(on_err)

SOEM.builder()\
    .with_state_check_interval(timedelta(milliseconds=100))\
    .with_on_err(on_err_func)
```

### Callback when link is lost

You can set a callback with `with_on_lost` function when an unrecoverable error (e.g., cable is unplugged) occurs[^fn_soem_err].
The callback take an error message as an argument.

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::SOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_on_lost(|msg| {
            eprintln!("Unrecoverable error occurred: {msg}");
            std::process::exit(-1);
        })
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

void on_lost(const char* msg) {
  std::cerr << "Link is lost\n";
  std::cerr << msg;
  exit(-1);
}

autd3::link::SOEM::builder()
    .with_on_lost(&on_lost)
```

```cs
var onLost = new SOEM.OnErrCallbackDelegate((string msg) =>
{
    Console.WriteLine($"Unrecoverable error occurred: {msg}");
    Environment.Exit(-1);
});

SOEM.Builder()
    .WithOnLost(onLost)
```

```python
from pyautd3.link.soem import SOEM, OnErrFunc

def on_lost(msg: ctypes.c_char_p):
    print(msg.decode("utf-8"), end="")
    os._exit(-1)

on_lost_func = OnErrFunc(on_lost)

SOEM.builder()\
    .with_on_lost(on_lost_func)
```

### Sync signal/Send cycle

`SOEM` might behave unstably when a large number of devices are connected[^fn_soem].
In this case, use the `with_sync0_cycle` and `with_send_cycle` functions to increase the values.

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::SOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_sync0_cycle(2)
    .with_send_cycle(2)
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

autd3::link::SOEM::builder()
    .with_sync0_cycle(2)
    .with_send_cycle(2)
```

```cs
SOEM.Builder()
    .WithSync0Cycle(2)
    .WithSendCycle(2)
```

```python
from pyautd3.link.soem import SOEM

SOEM.builder()\
    .with_sync0_cycle(2)\
    .with_send_cycle(2)
```

This value should be as small as possible without causing an error.

### Timer strategy

EhterCAT works by sending frames periodically at regular intervals.
You can specify how to send these periodic frames with `timer_strategy`.

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::SOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_timer_strategy(TimerStrategy::BusyWait)
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

autd3::link::SOEM::builder()
    .with_timer_strategy(autd3::TimerStrategy::BusyWait)
```

```cs
SOEM.Builder()
    .WithTimerStrategy(TimerStrategy.BusyWait)
```

```python
from pyautd3 import TimerStrategy
from pyautd3.link.soem import SOEM

SOEM.builder()\
    .with_timer_strategy(TimerStrategy.BusyWait)
```

* `Sleep`       : Use sleep function. Low resolution but low CPU load.
* `BusyWait`    : Use busywait (spinloop). High resolution but high CPU load.
* `NativeTimer` : Use OS native timer.
    - TimerQueueTimer on Windows, POSIX timer on Linux, Grand Central Dispatch Timer on macOS

The default is `Sleep`.

### Sync mode

You can set the EtherCAT sync mode (`DC` or `FreeRun`) with `with_sync_mode`.

- Please refer to [Beckhoff's explanation](https://infosys.beckhoff.com/english.php?content=../content/1033/ethercatsystem/2469122443.html&id=) for details.


```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::{SOEM, SyncMode};

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
SOEM::builder()
    .with_sync_mode(SyncMode::DC)
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

autd3::link::SOEM::builder()
    .with_sync_mode(autd3::link::SyncMode::DC)
```

```cs
SOEM.Builder()
    .WithSyncMode(SyncMode.Dc)
```

```python
from pyautd3.link.soem import SOEM, SyncMode

SOEM.builder()\
    .with_sync_mode(SyncMode.DC)
```

The default is `FreeRun`.

# RemoteSOEM

This link is used to separate the server PC running `SOEM` and the client PC running the user program.

To use `RemoteSOEM`, you need to prepare two PCs.
In this case, one PC must be able to use the `SOEM` link.
This PC is called the "server" here.
On the other hand, there are no particular restrictions on the PC on the development side that uses the SDK, and it is sufficient to be connected to the same LAN as the server.
This is called the "client" here.

First, connect the server and the AUTD device.
Then, connect the server and the client on different LANs[^fn_remote_soem].
Then, check the IP of the LAN between the server and the client.
For example, suppose the server is "172.16.99.104", and the client is "172.16.99.62".

## AUTD Server

To use `RemoteSOEM`, install `AUTD Server` first.
The AUTD server's installer is distributed on [GitHub Releases](https://github.com/shinolab/autd3/releases).

When you run `AUTD Server`, the following screen will appear, so open the "SOEM" tab.

<figure>
  <img src="../../fig/Users_Manual/autdserver_remotesoem.jpg"/>
</figure>

Set port number and click "Run" button.

## RemoteSOEM link API

`RemoteSOEM` constructor takes <server ip address:port> as an argument.

```rust,should_panic,edition2021
# extern crate autd3;
# extern crate autd3_link_soem;
# use autd3::prelude::*;
use autd3_link_soem::RemoteSOEM;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#            .open_with(
RemoteSOEM::builder("172.16.99.104:8080".parse()?)
# )?;
# Ok(())
# }
```

```cpp
#include "autd3/link/soem.hpp"

autd3::link::RemoteSOEM::builder("172.16.99.104:8080")
```

```cs
RemoteSOEM.Builder(new IPEndPoint(IPAddress.Parse("172.16.99.104"), 8080))
```

```python
from pyautd3.link.soem import RemoteSOEM

RemoteSOEM.builder("172.16.99.104:8080")
```

## SOEMAUTDServer

You can set options for `SOEM` with the option argument of `SOEMAUTDServer`.
Please see `SOEMAUTDServer --help` for details.

## Firewall

If you get a TCP-related error when using `RemoteSOEM`, it may be blocked by the firewall.

[^fn_soem]: It is looser than TwinCAT, and sometimes it works normally.

[^fn_soem_err]: It is unrecoverable, so there is nothing you can do but terminate it immediately.

[^fn_remote_soem]: It can be used even with wireless LAN.
