# Bundle

`Bundle`リンクは2つの`Link`まとめるためのものである.

```rust,should_panic
# use autd3::prelude::*;
use autd3_link_soem::SOEM;
use autd3_link_simulator::Simulator;
use autd3::link::Bundle;

# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#     .add_device(AUTD3::new(Vector3::new(0., 0., DEVICE_WIDTH), Vector3::new(0., PI/2.0, 0.)))
#            .open_with(
Bundle::new(SOEM::new(), Simulator::new(8080))
# )?;
# Ok(())
# }
```

最初に指定した`Link`が主となり, デバイスからの受信データは主のものが使用される.