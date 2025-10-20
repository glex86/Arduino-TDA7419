# TDA7419 Arduino Library

Arduino library to control the ST TDA7419 audio processor over I2C. It wraps the device registers with a friendly C++ API and works on AVR, ESP32, and other Arduino-compatible boards.

## Features

- Select input sources and input gains (main and second)
- Master volume and per-speaker volumes with soft-step support
- 3‑band tone control (bass, middle, treble) with frequency and Q options
- Loudness and mixing controls
- Subwoofer, spectrum analyzer configuration
- Mixing a separate mono channel to the speakers
- Highpass filter

## Goodies
Since the TDA7419 IC has a lot of adjustable registers and options, I created an additional C++ class that allows you to manage the infinite combination of settings in a transparent way, grouped into function groups.

## Getting started

1. Install via Arduino IDE by copying this folder as a library, or in PlatformIO by keeping it under `lib/TDA7419`.
2. Wire the chip to the I2C bus; default address is `0x44`.
3. Use the example sketch below or open `examples/Basic/Basic.ino`.

```cpp
#include <Wire.h>
#include <tda7419.hpp>

TDA7419::TDA7419 tda; // uses default Wire

void setup() {
  Serial.begin(115200);
  Wire.begin();
  tda.begin();

  tda.setMainSource(TDA7419::InputSource::SE1);
  tda.setMasterVolume(0);         // 0 dB
  tda.setBassLevel(3);
  tda.setTrebleLevel(2);
  tda.sendAllRegisters();
}

void loop() {}
```

Notes
- The library does not depend on any third‑party printing helpers. Debug output uses built-in `Serial` printing.
- For full register reference, see [docs/registers.md](docs/registers.md) or [docs/registers_new.md](docs/registers_new.md)
- The library contains codes generated using AI

## API surface
See [src/tda7419.hpp](src/tda7419.hpp) for the full list of setters/getters and enums.
See [src/tda7419Ctrl.hpp](srctda7419Ctrl.hpp) for the groupped wrappers.

## License
This library is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


## Credits
Copyright (c) 2025 Dávid Tamás
