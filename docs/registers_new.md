# TDA7419 Register Subaddresses

The Subaddress byte in I²C communication is built from the following bits:
**Testing mode [1] + AutoZero remain [1] + Auto Increment [1] + Subaddress [5]**

| A4 | A3 | A2 | A1 | A0 | Decimal | Description (Subaddress) | Source Table |
|:---|:---|:---|:---|:---|:----------|:-----------------------------------------------------|:-------------|
| 0 | 0 | 0 | 0 | 0 | **0** | Main source selector | Table 8 |
| 0 | 0 | 0 | 0 | 1 | **1** | Main loudness | Table 9 |
| 0 | 0 | 0 | 1 | 0 | **2** | Soft-mute / clock generator | Table 10 |
| 0 | 0 | 0 | 1 | 1 | **3** | Volume control | Table 11 |
| 0 | 0 | 1 | 0 | 0 | **4** | Treble filter | Table 12 |
| 0 | 0 | 1 | 0 | 1 | **5** | Middle filter | Table 13 |
| 0 | 0 | 1 | 1 | 0 | **6** | Bass filter | Table 14 |
| 0 | 0 | 1 | 1 | 1 | **7** | Second source selector | Table 15 |
| 0 | 1 | 0 | 0 | 0 | **8** | Subwoofer / middle / bass complementary settings | Table 16 |
| 0 | 1 | 0 | 0 | 1 | **9** | Mixing / gain effect | Table 17 |
| 0 | 1 | 0 | 1 | 0 | **10** | Speaker attenuator left front | Table 11 |
| 0 | 1 | 0 | 1 | 1 | **11** | Speaker attenuator right front | Table 11 |
| 0 | 1 | 1 | 0 | 0 | **12** | Speaker attenuator left rear | Table 11 |
| 0 | 1 | 1 | 0 | 1 | **13** | Speaker attenuator right rear | Table 11 |
| 0 | 1 | 1 | 1 | 0 | **14** | Mixing level control | Table 11 |
| 0 | 1 | 1 | 1 | 1 | **15** | Subwoofer attenuator | Table 11 |
| 1 | 0 | 0 | 0 | 0 | **16** | Spectrum analyzer / clock source / AC mode | Table 18 |
| 1 | 0 | 0 | 0 | 1 | **17** | Testing audio processor | Table 19 |

***

## Main Source Selector Register (0)

Register content (MSB to LSB):
**AutoZero [1] + Input Gain [4] + Source selector [3]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | AutoZero (AZ) | AutoZero function control. | **0**: ON - Internal offset cancellation (active on source change) <br> **1**: OFF |
| **6-3** | Input Gain (G) | Sets the main input gain. | **0000** = 0 dB ... **1111** = +15 dB (in 1 dB steps) |
| **2-0** | Source selector (SRC) | Selects the main audio input source. | **000**: QD (Quasi-Differential input)<br>**001**: SE1 (Single-Ended 1) <br> **010**: SE2 (Single-Ended 2) <br> **011**: SE3 (Single-Ended 3) <br> **100**: Mute |

***

## Main Loudness Register (1)

Register content (MSB to LSB):
**Loudness soft-step [1] + High frequency boost [1] + Center frequency [2] + Attenuation [4]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | Loudness soft-step (SS) | Enables soft-step transition for loudness setting. | **0**: ON <br> **1**: OFF |
| **6** | High boost (HB) | Enables the high frequency compensation for loudness. | **0**: ON <br> **1**: OFF |
| **5-4** | Center frequency (fP) | Frequency of the loudness curve's peak point. | **00**: Flat Mode <br> **01**: 400 Hz <br> **10**: 800 Hz <br> **11**: 2.4 kHz |
| **3-0** | Attenuation (ATTN) | The amount of loudness attenuation. | **0000** = 0 dB (Loudness OFF) ... **1111** = -15 dB |

***

## Soft-Mute / Clock Generator Register (2)

Register content (MSB to LSB):
**Clock fast mode [1] + Soft-step time [3] + Soft-mute time [2] + Pin influence for mute [1] + Soft-mute [1]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | Clock fast mode (FCM) | Frequency of the soft-step/soft-mute clock. | **0**: Normal Clock <br> **1**: Fast Clock |
| **6-4** | Soft-step time (SS T) | Soft-step transition time for volume/fader. | **000**: 0.160 ms (default) ... **111**: 20.48 ms (7 steps) |
| **3-2** | Soft-mute time (SM T) | Soft-mute/un-mute timing. | **00**: 0.48 ms <br> **01**: 0.96 ms <br> **10**: 123 ms <br> **11**: N/A |
| **1** | Pin influence (PI) | Enables the function of the external MUTE pin (Pin 21). | **0**: Mute pin active <br> **1**: Mute pin inactive (direct mute off) |
| **0** | Soft-mute (SM) | Enables the digital Soft-mute function. | **0**: Mute ON <br> **1**: Mute OFF |

***

## Volume (3), Speaker Attenuators (10-14), Subwoofer Attenuator (15) Registers

Registers 3, 10, 11, 12, 13, 14, and 15 use the same structure (Volume, Speaker/Mixer Attenuator):
Register content (MSB to LSB):
**Soft-step [1] + Attenuation/Gain [7]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | Soft-step (SS) | Enables soft-step transition for volume. | **0**: ON <br> **1**: OFF |
| **6-0** | Attenuation/Gain (ATTN/GAIN) | Sets the level in 1 dB steps. | **0000000** = -79 dB (Max Attenuation) ... **0100000** = 0 dB ... **0111111** = +15 dB (Max Gain) |

***

## Treble Filter Register (4)

Register content (MSB to LSB):
**DC gain [1] + Center frequency [2] + Treble Attenuation/Gain [5]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | DC gain (DCG) | Changes the DC gain. | **0**: Normal DC gain <br> **1**: Increased DC gain (for Shelving filter) |
| **6-5** | Center frequency (fC) | Center frequency of the Treble tone control. | **00**: 10 kHz <br> **01**: 12.5 kHz <br> **10**: 15 kHz <br> **11**: 17.5 kHz |
| **4-0** | Attenuation/Gain (ATTN/GAIN) | Treble gain/attenuation in 1 dB steps ($\pm 15\text{ dB}$). | **00000** = -15 dB ... **01111** = 0 dB ... **11111** = +15 dB |

***

## Middle Filter Register (5)

Register content (MSB to LSB):
**Q factor [2] + Center frequency [2] + Middle Attenuation/Gain [4]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7-6** | Q factor (Q) | Sets the bandwidth of the filter. | **00**: Q = 0.5 <br> **01**: Q = 0.75 <br> **10**: Q = 1.0 <br> **11**: Q = 1.25 |
| **5-4** | Center frequency (fC) | Center frequency of the Middle tone control. | **00**: 500 Hz <br> **01**: 1.0 kHz <br> **10**: 1.5 kHz <br> **11**: 2.5 kHz |
| **4-0** | Attenuation/Gain (ATTN/GAIN) | Middle gain/attenuation in 1 dB steps ($\pm 15\text{ dB}$). | **00000** = -15 dB ... **01111** = 0 dB ... **11111** = +15 dB |

***

## Bass Filter Register (6)

Register content (MSB to LSB):
**Q factor [2] + Center frequency [2] + Bass Attenuation/Gain [4]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7-6** | Q factor (Q) | Sets the bandwidth of the filter. | **00**: Q = 1.0 <br> **01**: Q = 1.25 <br> **10**: Q = 1.5 <br> **11**: Q = 2.0 |
| **5-4** | Center frequency (fC) | Center frequency of the Bass tone control. | **00**: 60 Hz <br> **01**: 80 Hz <br> **10**: 100 Hz <br> **11**: 200 Hz |
| **4-0** | Attenuation/Gain (ATTN/GAIN) | Bass gain/attenuation in 1 dB steps ($\pm 15\text{ dB}$). | **00000** = -15 dB ... **01111** = 0 dB ... **11111** = +15 dB |

***

## Second Source Selector Register (7)

Register content (MSB to LSB):
**AutoZero [1] + Input Gain [4] + Source selector [3]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | AutoZero (AZ) | AutoZero function control. | **0**: ON - Internal offset cancellation (active on source change) <br> **1**: OFF |
| **6-3** | Input Gain (G) | Sets the second input gain. | **0000** = 0 dB ... **1111** = +15 dB (in 1 dB steps) |
| **2-0** | Source selector (SRC) | Selects the second audio input source. | **000**: QD (Quasi-Differential input) <br> **001**: SE1 (Single-Ended Input 1) <br> **010**: SE2 (Single-Ended 2) <br> **011**: SE3 (Single-Ended 3) <br> **100**: Mute |

***

## Subwoofer / Middle / Bass Register (8)

Register content (MSB to LSB):
**Smoothing filter [1] + Bass DC mode [1] + Bass Center freq [2] + Middle Center freq [2] + Subwoofer cut-off freq [2]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | Smoothing filter (SF) | Enables/disables the smoothing filter. | **0**: ON <br> **1**: OFF |
| **6** | Bass DC mode (DC) | DC mode for the Bass tone control (for use as a shelving filter for cut-off). | **0**: ON <br> **1**: OFF |
| **5-4** | Bass Center freq (fC) | Center frequency of the Bass tone control (repetition from register 6). | **00**: 60 Hz <br> **01**: 80 Hz <br> **10**: 100 Hz <br> **11**: 200 Hz |
| **3-2** | Middle Center freq (fC) | Center frequency of the Middle tone control (repetition from register 5). | **00**: 500 Hz <br> **01**: 1000 Hz <br> **10**: 1500 Hz <br> **11**: 2500 Hz |
| **1-0** | Subwoofer cut-off freq (fLP) | Cut-off frequency of the Subwoofer Low-Pass Filter. | **00**: Flat <br> **01**: 80 Hz <br> **10**: 120 Hz <br> **11**: 160 Hz |

***

## Mixing / Gain Effect Register (9)

Register content (MSB to LSB):
**HPF filter gain effect [4] + Subwoofer enable [1] + Mixing enable [1] + Mixing to right front speaker [1] + Mixing to left front speaker [1]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7-4** | HPF Gain Effect (G HPF) | Sets the gain of the HPF filter (in 2 dB steps). | **0000** = 4 dB ... **1001** = 22 dB |
| **3** | Subwoofer enable (SW EN) | Enables/disables the Subwoofer output. | **0**: ON <br> **1**: OFF |
| **2** | Mixing enable (MIX EN) | Enables the mixing stage. | **0**: ON <br> **1**: OFF |
| **1** | Mixing right front (RF) | Adds the mix input to the right front output. | **0**: ON <br> **1**: OFF |
| **0** | Mixing left front (LF) | Adds the mix input to the left front output. | **0**: ON <br> **1**: OFF |

***

## Spectrum Analyzer / Clock Source / AC Mode Register (16)

Register content (MSB to LSB):
**SA Q factor [1] + SA Clock Source [1] + HPF enable [1] + AC mode [1] + Treble Q factor [2] + Loudness fP [2]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7** | SA Q factor (SAQ) | Selects the Q factor for the Spectrum Analyzer. | **0**: Low Q (Q1=1.8) <br> **1**: High Q (Q2=3.5) |
| **6** | SA Clock Source (SACLK) | Selects the clock source for the Spectrum Analyzer. | **0**: External Clock (SAIN pin) <br> **1**: Internal Clock |
| **5** | HPF enable (HPFEN) | Enables the High-Pass Filter. | **0**: OFF <br> **1**: ON |
| **4** | AC mode (ACEN) | Enables AC coupling mode. | **0**: OFF <br> **1**: ON |
| **3-2** | Treble Q factor (TQ) | Selects the Q factor for the Treble tone control. | **00**: Q1 (low) <br> **11**: Q4 (high) |
| **1-0** | Loudness fP (LFP) | Selects the Loudness center frequency (repetition from register 1). | **00**: Flat <br> **01**: 400 Hz <br> **10**: 800 Hz <br> **11**: 2.4 kHz |

***

## Audio Processor Testing Register (17)

Register content (MSB to LSB):
**Reserved [4] + Filter block to SA [4]**

| Bit(s) | Name | Description | Values |
|:--------|:----|:--------|:--------|
| **7-4** | Reserved | Always set to `0`. | **0000** |
| **3-0** | Filter block to SA (SA TEST) | Selects the source of the audio signal routed to the Spectrum Analyzer output (SAOUT) for internal testing. | **0000** = Main audio path ... **1111** = Treble output (16 steps) |