# Cache

`with_cache`によって`Gain`の計算結果をキャッシュする`Gain`を生成できる.

また, 振幅/位相データを変更する事もできる.

```rust
# use autd3::prelude::*;
# use autd3::link::Debug;
# #[allow(unused_variables)]
# fn main() -> Result<(), Box<dyn std::error::Error>> {
# let mut autd = Controller::builder()
#     .add_device(AUTD3::new(Vector3::zeros(), Vector3::zeros()))
#     .open_with(Debug::new())?;
let mut g = Null::new().with_cache(autd.geometry())?;
g[0].phase = 0.;
# Ok(())
# }
```

```cpp
// gは何らかのGain
autd3::gain::Cache c(g, autd.geometry());

c[0].phase = 0;
```