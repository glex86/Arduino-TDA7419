# TDA7419 Register subaddress
Registers subaddresses are constructed as the follow:
Testing mode [1] + AutoZero remain [1] + Auto Increment [1] + Subaddress [5]

Subaddress:
| A4 | A3 | A2 | A1 | A0 | Description                    |
|----|----|----|----|----|--------------------------------|
| 0  | 0  | 0  | 0  | 0  |  Main source selector |
| 0  | 0  | 0  | 0  | 1  |  Main loudness |
| 0  | 0  | 0  | 1  | 0  |  Soft-mute / clock generator |
| 0  | 0  | 0  | 1  | 1  |  Volume |
| 0  | 0  | 1  | 0  | 0  |  Treble |
| 0  | 0  | 1  | 0  | 1  |  Middle |
| 0  | 0  | 1  | 1  | 0  |  Bass |
| 0  | 0  | 1  | 1  | 1  |  Second source selector |
| 0  | 1  | 0  | 0  | 0  |  Subwoofer / middle / bass |
| 0  | 1  | 0  | 0  | 1  |  Mixing / gain effect |
| 0  | 1  | 0  | 1  | 0  |  Speaker attenuator left front |
| 0  | 1  | 0  | 1  | 1  |  Speaker attenuator right front |
| 0  | 1  | 1  | 0  | 0  |  Speaker attenuator left rear |
| 0  | 1  | 1  | 0  | 1  |  Speaker attenuator right rear |
| 0  | 1  | 1  | 1  | 0  |  Mixing level control |
| 0  | 1  | 1  | 1  | 1  |  Subwoofer attenuator |
| 1  | 0  | 0  | 0  | 0  |  Spectrum analyzer / clock source / AC mode |
| 1  | 0  | 0  | 0  | 1  |  Testing audio processor |


## Main source selector register (0)
Register content from MSB to LSB:
AutoZero [1] + Input Gain [4] + Source selector [3]

AutoZero: On/Off
Input gain: 0db - 15db
Source selector:
0: QD/SE: QD
1: SE1
2: SE2
3: SE3
4: mute

## Main loudness (1)
Register content from MSB to LSB:
Loudness soft-step [1] + High boost [1] + Center frequency [2] + Attenuation [4]

Loudness soft-step: On (0) | off (1)
High boost: On (0) | off (1)
Center frequency:
0: Flat
1: 400Hz
2: 800Hz
3: 2400Hz

Attenuation: 0db - -15db

## Soft-muta / Clock generator (2)
Register content from MSB to LSB:
Clock fast mode [0] + Soft-step time [3] + Soft-mute time [2] + Pin influence for mute [1] + Soft-mute [1]

Clock fast mode: On (0) | off (1)
Soft-step time:
0: 0.160ms
1: 0.321ms
2: 0. 642ms
3: 1.28ms
4: 2.56ms
5: 5.12ms
6: 10.24ms
7: 20.48ms

Soft-mute time:
0: 0.48ms
1: 0.96ms
2: 123ms

Pin influence for mute:
0: Pin and IIC
1: IIC

Soft-mute: On (0) | off (1)

## Volume / speaker / mixing / subwoofer attenuation (3, 10-15)
Register content from MSB to LSB:
Soft-step [1] + Gain / attenuation [7]

Soft-step: On (0) | off (1)
Gain / attenuation: +15db - -79db

## Treble Filter (4)
Register content from MSB to LSB:
Reference output select [1] + center frequency [2] + Gain/attenuation [5]

Reference output select:
0: External Vref (4 V)
1: Internal Vref (3.3 V)

center frequency:
0: 10.0 kHz
1: 12.5 kHz
2: 15.0 kHz
3: 17.5 kHz

Gain/attenuation: -15db - +15db

## Middle Filter (5)
Register content from MSB to LSB:
Soft-step [1] + Q factor [2] + Gain/attenuation [5]

Soft-step: On (0) | off (1)
Q factor:
0: 0.5
1: 0.75
2: 1
3: 1.25

Gain/attenuation: -15db - +15db

## Bass Filter (6)
Register content from MSB to LSB:
Soft-step [1] + Q factor [2] + Gain/attenuation [5]

Soft-step: On (0) | off (1)
Q factor:
0: 1
1: 1.25
2: 1.5
3: 2

Gain/attenuation: -15db - +15db

## Second source selector register (7)
Register content from MSB to LSB:
Rear Speaker Source [1] + Input Gain [4] + Source selector [3]

Rear Speaker Source: 0: main source 1: second source
Input gain: 0db - 15db
Source selector:
0: QD/SE: QD
1: SE1
2: SE2
3: SE3
4: mute

## Subwoofer / middle /bass (8)
Register content from MSB to LSB:
Smoothing filter [1] + Bass DC mode [1] + Bass Center freq [2] + Middle center freq [2] + Subwoofer cut-off freq [2]

Smoothing filter: On (0) | off (1)
Bass DC mode: On (0) | off (1)
Bass Center freq:
0: 60 Hz
1: 80 Hz
2: 100 Hz
3: 200 Hz

Middle center freq:
0: 500 Hz
1: 1000 Hz
2: 1500 Hz
3: 2500 Hz

Subwoofer cut-off freq:
0: flat
1: 80 Hz
2: 120 Hz
3: 160 Hz


## Mixing / gain effect (9)
Register content from MSB to LSB:
Gain effect for HPF filter [4] + Subwoofer enable [1] + Mixing enable [1] + Mixing to right front speaker [1] + Mixing to left front speaker [1]

Gain effect for HPF filter: 4db-22db by 2db steps
Subwoofer enable: On (0) | off (1)
Mixing enable: On (0) | off (1)
Mixing to right front speaker: On (0) | off (1)
Mixing to left front speaker: On (0) | off (1)

## Spectrum analyzer / clock source / AC mode (16)
Register content from MSB to LSB:
Coupling mode [2] + Clock source [1] + Reset [1] + Spectrum analyzer run [1] + Spectrum analyzer source [1] + Reset mode [1] + Spectrum analyzer filter Q factor [1]

Spectrum analyzer filter Q factor:
0: 3.5
1: 1.75

Reset mode:
0: IIC
1: Auto

Spectrum analyzer source:
0: Bass
1: In gain

Spectrum analyzer run: On (0) | off (1)
Reset: On (0) | off (1)
Clock source:
0: internal
1: external

Coupling mode: 
0: DC Coupling (without HPF)
1: AC coupling after In gain
2: DC Coupling (with HPF)
3: AC coupling after Bass

