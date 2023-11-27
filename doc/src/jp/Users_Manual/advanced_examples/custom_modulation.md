# Modulationの自作

`Modulation`も独自のものを作成することができる.
ここでは, 周期中のある一瞬だけ出力する`Burst`を作ってみる[^fn_burst].

以下が, この`Burst`のサンプルである.

```rust,edition2021
# extern crate autd3;
# extern crate tokio;
# extern crate autd3_driver;
use autd3::{
    derive::Modulation,
};
use autd3_driver::derive::prelude::*;

#[derive(Modulation, Clone, Copy)]
pub struct Burst {
    config: SamplingConfiguration,
}

impl Burst {
    pub fn new() -> Self {
        Self { config: SamplingConfiguration::new_with_frequency(4e3).unwrap() }
    }
}

impl Modulation for Burst {
    fn calc(&self) -> Result<Vec<EmitIntensity>, AUTDInternalError> {
        Ok((0..4000)
            .map(|i| if i == 3999 { EmitIntensity::MAX } else { EmitIntensity::MIN })
            .collect())
    }
}

# fn main() { 
# }
#
```

```cpp
class BurstModulation final : public autd3::Modulation {
public:
    std::vector<double> calc() const override {
        std::vector<double> buffer(_buf_size, 0);
        buffer[_buf_size - 1] = 1.0;
        return buffer;
    }

    explicit BurstModulation(const size_t buf_size = 4000, const uint32_t sampling_freq_div = 5120) noexcept
        : autd3::Modulation(sampling_freq_div), _buf_size(buf_size) {}

private:
    size_t _buf_size;
};
```

```cs
public class Burst : Modulation.Modulation
{
    private readonly int _length;

    public Burst(int length, uint sampleFreqDiv = 5120) : base(sampleFreqDiv)
    {
        _length = length;
    }

    public override double[] Calc()
    {
        var buf = new double[_length];
        buf[0] = 1;
        return buf;
    }
}
```

```python
from pyautd3.modulation import Modulation

class Burst(Modulation):
    _length: int

    def __init__(self, length: int, freq_div = 5120):
        super().__init__(freq_div)
        self._length = length

    def calc(self):
        buf = np.zeros(self._length)
        buf[0] = 1.0
        return buf
```

`Modulation`も`Gain`と同じく, `send`内部で`calc`メソッドが呼ばれ, その返り値の変調データが使用される.
したがって, この`calc`の中で, 変調データを計算すれば良い.

[^fn_burst]: SDKにはない.
