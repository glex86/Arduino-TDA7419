#include "tda7419.hpp"
#include <cmath>
#include <algorithm>
#include <Arduino.h>
#include <stdint.h>


namespace TDA7419 {

    // Local formatting helpers to keep the library self-contained (no external printHelpers dependency)
    namespace {
        template<typename T>
        constexpr T clampv(T value, T lo, T hi) {
            return (value < lo) ? lo : ((value > hi) ? hi : value);
        }

        inline void printHex2(uint8_t v) {
            if (v < 16) Serial.print('0');
            Serial.print(v, HEX);
        }

        inline void printBin8(uint8_t v) {
            for (int8_t b = 7; b >= 0; --b) {
                Serial.print((v >> b) & 0x01);
            }
        }
    }

    // Construct with an I2C interface (defaults to Wire)
    TDA7419::TDA7419(TwoWire& wire) : i2c(wire) {

        registers[ REG_MAIN_SOURCE       ].setValue(0x1A);          // Register 0
        registers[ REG_LOUDNESS_CONTROL  ].setValue(0x08);          // Register 1
        registers[ REG_SOFT_MUTE_CONTROL ].setValue(0xB7);          // Register 2
        registers[ REG_MASTER_VOLUME     ].setValue(0x00);          // Register 3
        registers[ REG_TREBLE_FILTER     ].setValue(0x80);          // Register 4
        registers[ REG_MIDDLE_FILTER     ].setValue(0x00);          // Register 5
        registers[ REG_BASS_FILTER       ].setValue(0x00);          // Register 6
        registers[ REG_SECOND_SOURCE     ].setValue(0x41);          // Register 7
        registers[ REG_SUB_MID_BASS      ].setValue(0xE0);          // Register 8
        registers[ REG_MIXING_CONTROL    ].setValue(0x27);          // Register 9
        registers[ REG_SPEAKER_LF_LEVEL  ].setValue(0x00);          // Register 10
        registers[ REG_SPEAKER_RF_LEVEL  ].setValue(0x00);          // Register 11
        registers[ REG_SPEAKER_LR_LEVEL  ].setValue(0x00);          // Register 12
        registers[ REG_SPEAKER_RR_LEVEL  ].setValue(0x00);          // Register 13
        registers[ REG_MIXING_LEVEL      ].setValue(0x00);          // Register 14
        registers[ REG_SUBWOOFER_LEVEL   ].setValue(0x00);          // Register 15
        registers[ REG_SPECTRUM_ANALYZER ].setValue(0x1C);          // Register 16
 
        //sendAllRegisters();
    }

    TDA7419::~TDA7419() = default;

    void TDA7419::begin() {
        sendAllRegisters();
    }

    // Main source selector. Register: 0, Bits: 0-2
    void TDA7419::setMainSource(InputSource source) {
        registers[REG_MAIN_SOURCE].writeValueAtBit(0, static_cast<uint8_t>(source), 3);
        inputChanged = true;
    }

    InputSource TDA7419::getMainSource() const {
        return static_cast<InputSource>(registers[REG_MAIN_SOURCE].readValueAtBit(0, 3));
    }

    // Main input gain (clamped). Register: 0, Bits: 3-6
    void TDA7419::setInputGain(uint8_t gain) {
        const uint8_t clampedGain = clampv<uint8_t>(gain, MIN_INPUT_GAIN, MAX_INPUT_GAIN);
        if (clampedGain != gain) {
            Serial.print("Input gain is clamped from ");
            Serial.print(gain);
            Serial.print(" to ");
            Serial.println(clampedGain);
        }
        registers[REG_MAIN_SOURCE].writeValueAtBit(3, clampedGain, 4);
    }

    uint8_t TDA7419::getInputGain() const {
        return registers[REG_MAIN_SOURCE].readValueAtBit(3, 4);
    }

    // Rear speaker source. Register: 7, Bit: 7
    void TDA7419::setRearSpeakerSource(RearSpeakerSource source) {
        registers[REG_SECOND_SOURCE].writeValueAtBit(7, static_cast<uint8_t>(source), 1);
        inputChanged = true;
    }

    RearSpeakerSource TDA7419::getRearSpeakerSource() const {
        return static_cast<RearSpeakerSource>(registers[REG_SECOND_SOURCE].readValueAtBit(7, 1));
    }

    // Second input source selector. Register: 7, Bits: 0-2
    void TDA7419::setSecondSource(InputSource source) {
        registers[REG_SECOND_SOURCE].writeValueAtBit(0, static_cast<uint8_t>(source), 3);
    }

    InputSource TDA7419::getSecondSource() const {
        return static_cast<InputSource>(registers[REG_SECOND_SOURCE].readValueAtBit(0, 3));
    }

    // Second source input gain (clamped). Register: 7, Bits: 3-6
    void TDA7419::setSecondSourceInputGain(uint8_t gain) {   
        const uint8_t clampedGain = clampv<uint8_t>(gain, MIN_INPUT_GAIN, MAX_INPUT_GAIN);
        if (clampedGain != gain) {
            Serial.print("Second source input gain is clamped from ");
            Serial.print(gain);
            Serial.print(" to ");
            Serial.println(clampedGain);
        }             
        registers[REG_SECOND_SOURCE].writeValueAtBit(3, clampedGain, 4);
    }

    uint8_t TDA7419::getSecondSourceInputGain() const {
        return registers[REG_SECOND_SOURCE].readValueAtBit(3, 4);
    }

    // AutoZero enable/disable. Register: 0, Bit: 7
    void TDA7419::setAutoZero(bool enable) {
        registers[REG_MAIN_SOURCE].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getAutoZero() const {
        return registers[REG_MAIN_SOURCE].readValueAtBit(7, 1) != 0;
    }

    // Main loudness attenuation control (4-bit). Register: 1, Bits: 0-3
    void TDA7419::setLoudnessAttenuation(uint8_t attenuation) {
        const uint8_t clampedAttenuation = clampv<uint8_t>(attenuation, MIN_INPUT_GAIN, MAX_INPUT_GAIN);
        if (clampedAttenuation != attenuation) {
            Serial.print("Loudness attenuation is clamped from ");
            Serial.print(attenuation);
            Serial.print(" to ");
            Serial.println(clampedAttenuation);
        }
        registers[REG_LOUDNESS_CONTROL].writeValueAtBit(0, clampedAttenuation, 4);
    }

    uint8_t TDA7419::getLoudnessAttenuation() const {
        return registers[REG_LOUDNESS_CONTROL].readValueAtBit(0, 4);
    }

    // Loudness center frequency. Register: 1, Bits: 4-5
    void TDA7419::setLoudnessCenterFreq(LoudnessCenterFreq freq) {
        registers[REG_LOUDNESS_CONTROL].writeValueAtBit(4, static_cast<uint8_t>(freq), 2);
    }

    LoudnessCenterFreq TDA7419::getLoudnessCenterFreq() const {
        return static_cast<LoudnessCenterFreq>(registers[REG_LOUDNESS_CONTROL].readValueAtBit(4, 2));
    }

    // Loudness high boost enable/disable. Register: 1, Bit: 6
    void TDA7419::setLoudnessHighBoost(bool enable) {
        registers[REG_LOUDNESS_CONTROL].writeValueAtBit(6, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getLoudnessHighBoost() const {
        return registers[REG_LOUDNESS_CONTROL].readValueAtBit(6, 1) != 0;
    }

    // Loudness soft-step enable/disable. Register: 1, Bit: 7
    void TDA7419::setLoudnessSoftStep(bool enable) {
        registers[REG_LOUDNESS_CONTROL].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getLoudnessSoftStep() const {
        return registers[REG_LOUDNESS_CONTROL].readValueAtBit(7, 1) != 0;
    }

    // Soft-mute enable/disable. Register: 2, Bit: 0
    void TDA7419::setSoftMute(bool enable) {
        registers[REG_SOFT_MUTE_CONTROL].writeValueAtBit(0, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSoftMute() const {
        return registers[REG_SOFT_MUTE_CONTROL].readValueAtBit(0, 1) != 0;
    }

    // Mute-pin enable/disable. Register: 2, Bit: 1
    void TDA7419::setMutePinEnable(bool enable) {
        registers[REG_SOFT_MUTE_CONTROL].writeValueAtBit(1, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMutePinEnable() const {
        return registers[REG_SOFT_MUTE_CONTROL].readValueAtBit(1, 1) != 0;
    }

    // Soft-mute time. Register: 2, Bits: 2-3
    void TDA7419::setSoftMuteTime(SoftMuteTime time) {
        registers[REG_SOFT_MUTE_CONTROL].writeValueAtBit(2, static_cast<uint8_t>(time), 2);
    }

    SoftMuteTime TDA7419::getSoftMuteTime() const {
        return static_cast<SoftMuteTime>(registers[REG_SOFT_MUTE_CONTROL].readValueAtBit(2, 2));
    }

    // Soft-step time. Register: 2, Bits: 4-6
    void TDA7419::setSoftStepTime(SoftStepTime time) {
        registers[REG_SOFT_MUTE_CONTROL].writeValueAtBit(4, static_cast<uint8_t>(time), 3);
    }

    SoftStepTime TDA7419::getSoftStepTime() const {
        return static_cast<SoftStepTime>(registers[REG_SOFT_MUTE_CONTROL].readValueAtBit(4, 3));
    }

    // Fast clock mode enable/disable. Register: 2, Bit: 7
    void TDA7419::setClockFastMode(bool enable) {
        registers[REG_SOFT_MUTE_CONTROL].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getClockFastMode() const {
        return registers[REG_SOFT_MUTE_CONTROL].readValueAtBit(7, 1) != 0;
    }

    // Master volume soft-step enable/disable. Register: 3, Bit: 7
    void TDA7419::setMasterVolumeSoftStep(bool enable) {
        registers[REG_MASTER_VOLUME].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMasterVolumeSoftStep() const {
        return registers[REG_MASTER_VOLUME].readValueAtBit(7, 1) != 0;
    }

    // Master volume -80 to 15 (7-bit). Register: 3, Bits: 0-6
    void TDA7419::setMasterVolume(int8_t volume) {
        const int8_t clampedVolume = clampv<int8_t>(volume, MIN_SPEAKER_VOLUME, MAX_SPEAKER_VOLUME);
        if (clampedVolume != volume) {
            Serial.print("Master volume is clamped from ");
            Serial.print(volume);
            Serial.print(" to ");
            Serial.println(clampedVolume);
        }
        registers[REG_MASTER_VOLUME].writeValueAtBit(0, convertVolumeToRegisterValue(clampedVolume), 7);
    }

    int8_t TDA7419::getMasterVolume() const {
        return convertRegisterValueToVolume(registers[REG_MASTER_VOLUME].readValueAtBit(0, 7));
    }

    // Treble level (5-bit). Register: 4, Bits: 0-4
    void TDA7419::setTrebleLevel(int8_t level) {
        const int8_t clampedLevel = clampv<int8_t>(level, MIN_EQ_LEVEL, MAX_EQ_LEVEL);
        if (clampedLevel != level) {
            Serial.print("Treble level is clamped from ");
            Serial.print(level);
            Serial.print(" to ");
            Serial.println(clampedLevel);
        }
        registers[REG_TREBLE_FILTER].writeValueAtBit(0, convertEQLevelToRegisterValue(clampedLevel), 5);
    }

    int8_t TDA7419::getTrebleLevel() const {
        return convertRegisterValueToEQLevel(registers[REG_TREBLE_FILTER].readValueAtBit(0, 5));
    }

    // Treble center frequency. Register: 4, Bits: 5-6
    void TDA7419::setTrebleCenterFreq(TrebleCenterFreq freq) {
        registers[REG_TREBLE_FILTER].writeValueAtBit(5, static_cast<uint8_t>(freq), 2);
    }

    TrebleCenterFreq TDA7419::getTrebleCenterFreq() const {
        return static_cast<TrebleCenterFreq>(registers[REG_TREBLE_FILTER].readValueAtBit(5, 2));
    }

    // Treble reference select (internal/external). Register: 4, Bit: 7
    void TDA7419::setTrebleReferenceInternal(bool useInternalReference) {
        registers[REG_TREBLE_FILTER].writeValueAtBit(7, useInternalReference ? 1u : 0u, 1);
    }

    bool TDA7419::getTrebleReferenceInternal() const {
        return registers[REG_TREBLE_FILTER].readValueAtBit(7, 1) != 0;
    }

    // Middle soft-step enable/disable. Register: 5, Bit: 7
    void TDA7419::setMiddleSoftStep(bool enable) {
        registers[REG_MIDDLE_FILTER].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMiddleSoftStepEnabled() const {
        return registers[REG_MIDDLE_FILTER].readValueAtBit(7, 1) != 0;
    }

    // Middle gain (5-bit). Register: 5, Bits: 0-4
    void TDA7419::setMiddleLevel(int8_t gain) {
        const int8_t clampedGain = clampv<int8_t>(gain, MIN_EQ_LEVEL, MAX_EQ_LEVEL);
        if (clampedGain != gain) {
            Serial.print("Middle gain is clamped from ");
            Serial.print(gain);
            Serial.print(" to ");
            Serial.println(clampedGain);
        }        
        registers[REG_MIDDLE_FILTER].writeValueAtBit(0, convertEQLevelToRegisterValue(clampedGain), 5);
    }

    int8_t TDA7419::getMiddleLevel() const {
        return convertRegisterValueToEQLevel(registers[REG_MIDDLE_FILTER].readValueAtBit(0, 5));
    }

    // Middle Q factor. Register: 5, Bits: 5-6
    void TDA7419::setMiddleQFactor(MiddleQFactor q) {
        registers[REG_MIDDLE_FILTER].writeValueAtBit(5, static_cast<uint8_t>(q), 2);
    }

    MiddleQFactor TDA7419::getMiddleQFactor() const {
        return static_cast<MiddleQFactor>(registers[REG_MIDDLE_FILTER].readValueAtBit(5, 2));
    }

    // Bass soft-step enable/disable. Register: 6, Bit: 7
    void TDA7419::setBassSoftStep(bool enable) {
        registers[REG_BASS_FILTER].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getBassSoftStep() const {
        return registers[REG_BASS_FILTER].readValueAtBit(7, 1) != 0;
    }

    // Bass level (-15 - +15). Register: 6, Bits: 0-4
    void TDA7419::setBassLevel(int8_t level) {
        const int8_t clampedLevel = clampv<int8_t>(level, MIN_EQ_LEVEL, MAX_EQ_LEVEL);
        if (clampedLevel != level) {
            Serial.print("Bass level is clamped from ");
            Serial.print(level);
            Serial.print(" to ");
            Serial.println(clampedLevel);
        }
        registers[REG_BASS_FILTER].writeValueAtBit(0, convertEQLevelToRegisterValue(clampedLevel), 5);
    }

    int8_t TDA7419::getBassLevel() const {
        return convertRegisterValueToEQLevel(registers[REG_BASS_FILTER].readValueAtBit(0, 5));
    }

    // Bass Q factor. Register: 6, Bits: 5-6
    void TDA7419::setBassQFactor(BassQFactor q) {
        registers[REG_BASS_FILTER].writeValueAtBit(5, static_cast<uint8_t>(q), 2);
    }

    BassQFactor TDA7419::getBassQFactor() const {
        return static_cast<BassQFactor>(registers[REG_BASS_FILTER].readValueAtBit(5, 2));
    }

    // Smoothing filter enable/disable. Register: 8, Bit: 7
    void TDA7419::setSmoothingFilter(bool enable) {
        registers[REG_SUB_MID_BASS].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSmoothingFilter() const {
        return registers[REG_SUB_MID_BASS].readValueAtBit(7, 1) != 0;
    }

    // Bass DC mode enable/disable. Register: 8, Bit: 6
    void TDA7419::setBassDcMode(bool enable) {
        registers[REG_SUB_MID_BASS].writeValueAtBit(6, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getBassDcMode() const {
        return registers[REG_SUB_MID_BASS].readValueAtBit(6, 1) != 0;
    }

    // Bass center frequency. Register: 8, Bits: 4-5
    void TDA7419::setBassCenterFreq(BassCenterFreq freq) {
        registers[REG_SUB_MID_BASS].writeValueAtBit(4, static_cast<uint8_t>(freq), 2);
    }

    BassCenterFreq TDA7419::getBassCenterFreq() const {
        return static_cast<BassCenterFreq>(registers[REG_SUB_MID_BASS].readValueAtBit(4, 2));
    }

    // Middle center frequency. Register: 8, Bits: 2-3
    void TDA7419::setMiddleCenterFreq(MiddleCenterFreq freq) {
        registers[REG_SUB_MID_BASS].writeValueAtBit(2, static_cast<uint8_t>(freq), 2);
    }

    MiddleCenterFreq TDA7419::getMiddleCenterFreq() const {
        return static_cast<MiddleCenterFreq>(registers[REG_SUB_MID_BASS].readValueAtBit(2, 2));
    }

    // Subwoofer cutoff frequency. Register: 8, Bits: 0-1
    void TDA7419::setSubCutoffFreq(SubCutoffFreq freq) {
        registers[REG_SUB_MID_BASS].writeValueAtBit(0, static_cast<uint8_t>(freq), 2);
    }

    SubCutoffFreq TDA7419::getSubCutoffFreq() const {
        return static_cast<SubCutoffFreq>(registers[REG_SUB_MID_BASS].readValueAtBit(0, 2));
    }

    // Mixing gain effect. Register: 9, Bits: 4-7
    void TDA7419::setMixingGainEffect(MixingGainEffect effect) {
        registers[REG_MIXING_CONTROL].writeValueAtBit(4, static_cast<uint8_t>(effect), 4);
    }

    MixingGainEffect TDA7419::getMixingGainEffect() const {
        return static_cast<MixingGainEffect>(registers[REG_MIXING_CONTROL].readValueAtBit(4, 4));
    }

    // Subwoofer enable/disable. Register: 9, Bit: 3
    void TDA7419::setSubwooferEnable(bool enable) {
        registers[REG_MIXING_CONTROL].writeValueAtBit(3, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSubwooferEnable() const {
        return registers[REG_MIXING_CONTROL].readValueAtBit(3, 1) != 0;
    }

    // Mixing enable/disable. Register: 9, Bit: 2
    void TDA7419::setMixingEnable(bool enable) {
        registers[REG_MIXING_CONTROL].writeValueAtBit(2, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMixingEnable() const {
        return registers[REG_MIXING_CONTROL].readValueAtBit(2, 1) != 0;
    }

    // Route mix to right front. Register: 9, Bit: 1
    void TDA7419::setMixToRightFront(bool enable) {
        registers[REG_MIXING_CONTROL].writeValueAtBit(1, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMixToRightFront() const {
        return registers[REG_MIXING_CONTROL].readValueAtBit(1, 1) != 0;
    }

    // Route mix to left front. Register: 9, Bit: 0
    void TDA7419::setMixToLeftFront(bool enable) {
        registers[REG_MIXING_CONTROL].writeValueAtBit(0, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMixToLeftFront() const {
        return registers[REG_MIXING_CONTROL].readValueAtBit(0, 1) != 0;
    }

    // Speaker soft-step for channel. Register: (10 + channel), Bit: 7
    void TDA7419::setSpeakerSoftStep(SpeakerChannel channel, bool enable) {
        const uint8_t index = REG_SPEAKER_LF_LEVEL + static_cast<uint8_t>(channel);
        registers[index].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSpeakerSoftStep(SpeakerChannel channel) const {
        const uint8_t index = REG_SPEAKER_LF_LEVEL + static_cast<uint8_t>(channel);
        return registers[index].readValueAtBit(7, 1) != 0;
    }

    // Speaker volume for channel (7-bit). Register: (10 + channel), Bits: 0-6
    void TDA7419::setSpeakerVolume(SpeakerChannel channel, int8_t volume) {
        const int8_t clampedVolume = clampv<int8_t>(volume, MIN_SPEAKER_VOLUME, MAX_SPEAKER_VOLUME);
        if (clampedVolume != volume) {
            Serial.print("Speaker(");
            Serial.print(static_cast<uint8_t>(channel));
            Serial.print(") volume is clamped from ");
            Serial.print(volume);
            Serial.print(" to ");
            Serial.println(clampedVolume);
        }
        const uint8_t index = REG_SPEAKER_LF_LEVEL + static_cast<uint8_t>(channel);
        registers[index].writeValueAtBit(0, convertVolumeToRegisterValue(clampedVolume), 7);
    }

    int8_t TDA7419::getSpeakerVolume(SpeakerChannel channel) const {
        const uint8_t index = REG_SPEAKER_LF_LEVEL + static_cast<uint8_t>(channel);
        return convertRegisterValueToVolume(registers[index].readValueAtBit(0, 7));
    }

    // Mixing channel soft-step. Register: 14, Bit: 7
    void TDA7419::setMixingChannelSoftStep(bool enable) {
        registers[REG_MIXING_LEVEL].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getMixingChannelSoftStep() const {
        return registers[REG_MIXING_LEVEL].readValueAtBit(7, 1) != 0;
    }

    // Mixing channel volume (-80 - +15). Register: 14, Bits: 0-6
    void TDA7419::setMixingChannelVolume(int8_t volume) {
        const int8_t clampedVolume = clampv<int8_t>(volume, MIN_SPEAKER_VOLUME, MAX_SPEAKER_VOLUME);
        if (clampedVolume != volume) {
            Serial.print("Mixing channel volume is clamped from ");
            Serial.print(volume);
            Serial.print(" to ");
            Serial.println(clampedVolume);
        }
        registers[REG_MIXING_LEVEL].writeValueAtBit(0, convertVolumeToRegisterValue(clampedVolume), 7);
    }

    int8_t TDA7419::getMixingChannelVolume() const {
        return convertRegisterValueToVolume(registers[REG_MIXING_LEVEL].readValueAtBit(0, 7));
    }

    // Subwoofer soft-step. Register: 15, Bit: 7
    void TDA7419::setSubwooferSoftStep(bool enable) {
        registers[REG_SUBWOOFER_LEVEL].writeValueAtBit(7, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSubwooferSoftStep() const {
        return registers[REG_SUBWOOFER_LEVEL].readValueAtBit(7, 1) != 0;
    }

    // Subwoofer volume (-80 - +15). Register: 15, Bits: 0-6
    void TDA7419::setSubwooferVolume(int8_t volume) {
        const int8_t clampedVolume = clampv<int8_t>(volume, MIN_SPEAKER_VOLUME, MAX_SPEAKER_VOLUME);
        if (clampedVolume != volume) {
            Serial.print("Subwoofer volume is clamped from ");
            Serial.print(volume);
            Serial.print(" to ");
            Serial.println(clampedVolume);
        }
        registers[REG_SUBWOOFER_LEVEL].writeValueAtBit(0, convertVolumeToRegisterValue(clampedVolume), 7);
    }

    int8_t TDA7419::getSubwooferVolume() const {
        return convertRegisterValueToVolume(registers[REG_SUBWOOFER_LEVEL].readValueAtBit(0, 7));
    }

    // Spectrum coupling mode. Register: 16, Bits: 6-7
    void TDA7419::setSpectrumCouplingMode(SpectrumCouplingMode mode) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(6, static_cast<uint8_t>(mode), 2);
    }

    SpectrumCouplingMode TDA7419::getSpectrumCouplingMode() const {
        return static_cast<SpectrumCouplingMode>(registers[REG_SPECTRUM_ANALYZER].readValueAtBit(6, 2));
    }

    // External clock select. Register: 16, Bit: 5
    void TDA7419::setExternalClock(bool useExternal) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(5, useExternal ? 1u : 0u, 1);
    }

    bool TDA7419::getExternalClock() const {
        return registers[REG_SPECTRUM_ANALYZER].readValueAtBit(5, 1) != 0;
    }

    // Spectrum reset. Register: 16, Bit: 4
    void TDA7419::setSpectrumReset(bool enable) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(4, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSpectrumReset() const {
        return registers[REG_SPECTRUM_ANALYZER].readValueAtBit(4, 1) != 0;
    }

    // Spectrum run. Register: 16, Bit: 3
    void TDA7419::setSpectrumRun(bool enable) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(3, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSpectrumRun() const {
        return registers[REG_SPECTRUM_ANALYZER].readValueAtBit(3, 1) != 0;
    }

    // Spectrum source. Register: 16, Bit: 2
    void TDA7419::setSpectrumSource(SpectrumSource source) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(2, static_cast<uint8_t>(source), 1);
    }

    SpectrumSource TDA7419::getSpectrumSource() const {
        return static_cast<SpectrumSource>(registers[REG_SPECTRUM_ANALYZER].readValueAtBit(2, 1));
    }

    // Spectrum auto-reset enable/disable. Register: 16, Bit: 1
    void TDA7419::setSpectrumAutoReset(bool enable) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(1, enable ? 1u : 0u, 1);
    }

    bool TDA7419::getSpectrumAutoReset() const {
        return registers[REG_SPECTRUM_ANALYZER].readValueAtBit(1, 1) != 0;
    }

    // Spectrum filter Q. Register: 16, Bit: 0
    void TDA7419::setSpectrumFilterQ(SpectrumFilterQ filterQ) {
        registers[REG_SPECTRUM_ANALYZER].writeValueAtBit(0, static_cast<uint8_t>(filterQ), 1);
    }

    SpectrumFilterQ TDA7419::getSpectrumFilterQ() const {
        return static_cast<SpectrumFilterQ>(registers[REG_SPECTRUM_ANALYZER].readValueAtBit(0, 1));
    }


    void TDA7419::printTransmissionError(uint8_t errorCode) const
    {
        switch (errorCode)
        {
        case 1:
            Serial.println(F("TDA7419: Error 1 - Data too long to fit in transmit buffer."));
            break;
        case 2:
            Serial.println(F("TDA7419: Error 2 - Received NACK on transmit of address."));
            break;
        case 3:
            Serial.println(F("TDA7419: Error 3 - Received NACK on transmit of data."));
            break;
        case 4:
            Serial.println(F("TDA7419: Error 4 - Other error."));
            break;
        case 5:
            Serial.println(F("TDA7419: Error 5 - Timeout."));
            break;

        default:
            Serial.print(F("TDA7419: Error "));
            Serial.println(errorCode);
            break;
        }
    }

    //send all the registers to the device
    bool TDA7419::sendAllRegisters() {
        if (debug) {
            printRegistersDebug();
            Serial.println(F("TDA7419: Sending all registers"));
        }

        i2c.beginTransmission(TDA7419_I2C_ADDRESS);
        i2c.write(SUBADDR_AUTO_INCREMENT_BIT + (inputChanged ? 0 : SUBADDR_AUTOZERO_REMAIN_BIT)); // subaddress starting command (document this)
        for (uint8_t reg = 0; reg < REGISTER_COUNT; ++reg) {
            i2c.write(registers[reg].getValue());
        }
        
        uint8_t status = i2c.endTransmission();
        if (status != 0) {
            printTransmissionError(status);
            // Optionally log via Serial.print for Arduino/ESP32 or return status
            return false;
        }
        
        // only clear changed if transfer succeeded
        for (uint8_t reg = 0; reg < REGISTER_COUNT; ++reg) {
            registers[reg].clearChanged();
        }

        inputChanged = false;
        return true;
    }

    bool TDA7419::sendChangedRegisters() {
        if (debug) {
            printRegistersDebug();
            Serial.println(F("TDA7419: Sending changed registers"));
        }

        for (uint8_t reg = 0; reg < REGISTER_COUNT; ++reg) {
            if (registers[reg].isChanged()) {
                if (debug) {
                    Serial.print(F("TDA7419: Sending register "));
                    Serial.println(reg);
                }
                i2c.beginTransmission(TDA7419_I2C_ADDRESS);
                i2c.write(((reg == REG_MAIN_SOURCE && inputChanged) ? 0 : SUBADDR_AUTOZERO_REMAIN_BIT) + reg); // incremental single-subaddress write
                i2c.write(registers[reg].getValue());
                uint8_t status = i2c.endTransmission();
                if (status != 0) {
                    printTransmissionError(status);
                    return false;
                }
                registers[reg].clearChanged();
            }
        }
        return true;
    }

    void TDA7419::printRegistersDebug() const
    {
        Serial.println(F("\n--[ TDA7419 DEBUG ]---------------------"));
        for (uint8_t reg = 0; reg < REGISTER_COUNT; ++reg) {
            Serial.print(F("Register "));
            Serial.print(reg);
            if (registers[reg].isChanged()) {
                Serial.print(F("* "));
            }
            else {
                Serial.print(F("  "));
            }
            Serial.print(F(": "));
            printHex2(registers[reg].getValue());
            Serial.print(F(" | "));
            printBin8(registers[reg].getValue());
            Serial.println();
        }

        Serial.println(F("---------------------------------------\n"));
    }

    // Map volume range (-79 to 15) to register value. -80 to mute
    uint8_t TDA7419::convertVolumeToRegisterValue(int8_t volume) const
    {
        if (volume < -80) volume = -80;
        if (volume > 15) volume = 15;

        uint8_t regValue = 0;

        if (volume >= 0) {
            regValue = static_cast<uint8_t>(volume);
        }
        else {
            regValue = abs(volume) + 16;
        }

        return regValue;
    }

    int8_t TDA7419::convertRegisterValueToVolume(uint8_t regValue) const
    {
        int8_t volume = 0;

        if (regValue < 16) {
            volume = static_cast<int8_t>(regValue);
        }
        else {
            volume = static_cast<int8_t>(regValue - 16) * -1;
        }

        return volume;
    }

    uint8_t TDA7419::convertEQLevelToRegisterValue(int8_t gain) const
    {
        if (gain < -15) gain = -15;
        if (gain > 15) gain = 15;

        uint8_t regValue = 0;
        if (gain >= 0) {
            regValue = static_cast<uint8_t>(gain) + 16;
        }
        else {
            regValue = abs(gain);
        }

        return regValue;
    }

    int8_t TDA7419::convertRegisterValueToEQLevel(uint8_t regValue) const
    {
        int8_t gain = 0;

        if (regValue < 16) {
            gain = static_cast<int8_t>(regValue) * -1;
        }
        else {
            gain = static_cast<int8_t>(regValue - 16);
        }

        return gain;
    }


} // namespace TDA7419
