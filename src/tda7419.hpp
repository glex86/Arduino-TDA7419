#pragma once

#include <cstdint>
#include <array>        // added
#include <Wire.h>
#include "bitStorage.hpp"


namespace TDA7419 {
    constexpr uint8_t TDA7419_I2C_ADDRESS = 0x44;
    constexpr uint8_t TDA7419_MAX_INPUT_GAIN = 15;
    constexpr uint8_t SUBADDR_AUTOZERO_REMAIN_BIT = 0x40; // mute
    constexpr uint8_t SUBADDR_AUTO_INCREMENT_BIT = 0x20; // start autozero

    // number of device registers
    constexpr size_t REGISTER_COUNT = 17;

    // register indices (self-documenting)
    // Replaced enum class RegisterIndex with constexpr uint8_t constants
    constexpr uint8_t REG_MAIN_SOURCE = 0;
    constexpr uint8_t REG_LOUDNESS_CONTROL = 1;
    constexpr uint8_t REG_SOFT_MUTE_CONTROL = 2;
    constexpr uint8_t REG_MASTER_VOLUME = 3;
    constexpr uint8_t REG_TREBLE_FILTER = 4;
    constexpr uint8_t REG_MIDDLE_FILTER = 5;
    constexpr uint8_t REG_BASS_FILTER = 6;
    constexpr uint8_t REG_SECOND_SOURCE = 7;
    constexpr uint8_t REG_SUB_MID_BASS = 8;
    constexpr uint8_t REG_MIXING_CONTROL = 9;
    constexpr uint8_t REG_SPEAKER_LF_LEVEL = 10;
    constexpr uint8_t REG_SPEAKER_RF_LEVEL = 11;
    constexpr uint8_t REG_SPEAKER_LR_LEVEL = 12;
    constexpr uint8_t REG_SPEAKER_RR_LEVEL = 13;
    constexpr uint8_t REG_MIXING_LEVEL = 14;
    constexpr uint8_t REG_SUBWOOFER_LEVEL = 15;
    constexpr uint8_t REG_SPECTRUM_ANALYZER = 16;

    constexpr uint8_t MIN_INPUT_GAIN = 0;
    constexpr uint8_t MAX_INPUT_GAIN = 15;
    constexpr int8_t MIN_SPEAKER_VOLUME = -80;
    constexpr int8_t MAX_SPEAKER_VOLUME = 15;
    constexpr int8_t MIN_EQ_LEVEL = -15;
    constexpr int8_t MAX_EQ_LEVEL = 15;

#pragma region Enumerations for various settings
    /** 
     * @brief Input source selector.
     * @details Corresponds to register 0 bits [2:0].
     */
    enum class InputSource : uint8_t {
        QD = 0,
        SE1 = 1,
        SE2 = 2,
        SE3 = 3,
        Mute = 4
    };

    /**
     * @brief Loudness center frequency selection.
     * @details Corresponds to register 1 bits [5:4].
     */
    enum class LoudnessCenterFreq : uint8_t {
        Flat = 0,
        Hz400 = 1,
        Hz800 = 2,
        Hz2400 = 3
    };

    /**
     * @brief Bass center frequency selection.
     * @details Corresponds to register 8 bits [5:4].
     */
    enum class BassCenterFreq : uint8_t {
        Hz60 = 0,
        Hz80 = 1,
        Hz100 = 2,
        Hz200 = 3
    };

    /**
     * @brief Middle center frequency selection.
     * @details Corresponds to register 8 bits [3:2].
     */
    enum class MiddleCenterFreq : uint8_t {
        Hz500 = 0,
        Hz1000 = 1,
        Hz1500 = 2,
        Hz2500 = 3
    };

    /**
     * @brief Treble center frequency selection.
     * @details Corresponds to register 4 bits [6:5].
     */
    enum class TrebleCenterFreq : uint8_t {
        KHz10 = 0,
        KHz12_5 = 1,
        KHz15 = 2,
        KHz17_5 = 3
    };

    /**
     * @brief Subwoofer cutoff frequency selection.
     * @details Corresponds to register 8 bits [1:0].
     */
    enum class SubCutoffFreq : uint8_t {
        Flat = 0,
        Hz80 = 1,
        Hz120 = 2,
        Hz160 = 3
    };

    /**
     * @brief Middle Q factor selection.
     * @details Corresponds to register 5 bits [6:5].
     */
    enum class MiddleQFactor : uint8_t {
        Q0_5 = 0,
        Q0_75 = 1,
        Q1 = 2,
        Q1_25 = 3
    };

    /**
     * @brief Bass Q factor selection.
     * @details Corresponds to register 6 bits [6:5].
     */
    enum class BassQFactor : uint8_t {
        Q1 = 0,
        Q1_25 = 1,
        Q1_5 = 2,
        Q2 = 3
    };

    /**
     * @brief Mixing gain effect (HPF filter gain) selection.
     * @details Corresponds to register 9 bits [7:4].
     */
    enum class MixingGainEffect : uint8_t {
        dB4 = 0,
        dB6 = 1,
        dB8 = 2,
        dB10 = 3,
        dB12 = 4,
        dB14 = 5,
        dB16 = 6,
        dB18 = 7,
        dB20 = 8,
        dB22 = 9
    };

    /**
     * @brief Spectrum analyzer coupling mode.
     * @details Corresponds to register 16 bits [7:6].
     */
    enum class SpectrumCouplingMode : uint8_t {
        DC_wo_HPF = 0,
        AC_after_InGain = 1,
        DC_w_HPF = 2,
        AC_after_Bass = 3
    };

    /**
     * @brief Spectrum analyzer source selection.
     * @details Corresponds to register 16 bit [2].
     */
    enum class SpectrumSource : uint8_t {
        Bass = 0,
        InGain = 1
    };

    /**
     * @brief Spectrum analyzer filter Q selection.
     * @details Corresponds to register 16 bit [0].
     */
    enum class SpectrumFilterQ : uint8_t {
        Q3_5 = 0,
        Q1_75 = 1
    };

    /**
     * @brief Speaker channel selector used for per-channel settings.
     * @details Maps to registers 10..13 (LeftFront..RightRear).
     */
    enum class SpeakerChannel : uint8_t {
        LeftFront = 0,
        RightFront = 1,
        LeftRear = 2,
        RightRear = 3
    };

    /**
     * @brief Soft-mute ramp time selection.
     * @details Corresponds to register 2 bits [3:2].
     */
    enum class SoftMuteTime : uint8_t {
        Ms048 = 0,
        Ms096 = 1,
        Ms123 = 2,
    };

    /**
     * @brief Soft-step time selection for smooth transitions.
     * @details Corresponds to register 2 bits [6:4].
     */
    enum class SoftStepTime : uint8_t {
        Us160 = 0,
        Us320 = 1,
        Us640 = 2,
        Us1280 = 3,
        Us2560 = 4,
        Us5120 = 5,
        Us10240 = 6,
        Us20480 = 7
    };

    /**
     * @brief Rear speaker source selection.
     * @details Corresponds to register 7 bit [7].
     */
    enum class RearSpeakerSource : uint8_t {
        mainSource = 0,
        secondSource = 1
    };
#pragma endregion


    /**
     * @brief High-level driver for the TDA7419 audio processor.
     * @details Provides setters/getters for all chip features. All methods that
     * read or write device state document the affected register and bit positions.
     */
    class TDA7419 {
    public:
        bool debug = false;

        // Construct with an I2C interface (defaults to Wire)
        TDA7419(TwoWire& wire = Wire);
        ~TDA7419();

        void begin();

        /** 
         * @brief Set the main input source.
         * @param source InputSource enum value to select.
         * @note Affects register 0, bits [2:0].
         */
        void setMainSource(InputSource source);
        /**
         * @brief Get the current main input source.
         * @return InputSource current selection.
         * @note Reads register 0, bits [2:0].
         */
        InputSource getMainSource() const;

        /**
         * @brief Set the main input gain (0-15).
         * @param gain Gain value in range [0..15].
         * @note Affects register 0, bits [6:3].
         */
        void setInputGain(uint8_t gain);
        /**
         * @brief Get the current main input gain.
         * @return uint8_t gain in range [0..15].
         * @note Reads register 0, bits [6:3].
         */
        uint8_t getInputGain() const;

        /**
         * @brief Set the rear speaker source selection.
         * @param source RearSpeakerSource enum value.
         * @note Affects register 7, bit 7.
         */
        void setRearSpeakerSource(RearSpeakerSource source);
        /**
         * @brief Get the rear speaker source selection.
         * @return RearSpeakerSource current selection.
         * @note Reads register 7, bit 7.
         */
        RearSpeakerSource getRearSpeakerSource() const;

        /**
         * @brief Set the second input source selection.
         * @param source InputSource enum value.
         * @note Affects register 7, bits [2:0].
         */
        void setSecondSource(InputSource source);
        /**
         * @brief Get the second input source selection.
         * @return InputSource current selection.
         * @note Reads register 7, bits [2:0].
         */
        InputSource getSecondSource() const;

        /**
         * @brief Set the second source input gain (0-15).
         * @param gain Gain value [0..15].
         * @note Affects register 7, bits [6:3].
         */
        void setSecondSourceInputGain(uint8_t gain);
        /**
         * @brief Get the second source input gain.
         * @return uint8_t gain [0..15].
         * @note Reads register 7, bits [6:3].
         */
        uint8_t getSecondSourceInputGain() const;

        /**
         * @brief Enable or disable AutoZero.
         * @param enable true to enable AutoZero, false to disable.
         * @note Affects register 0, bit 7.
         */
        void setAutoZero(bool enable);
        /**
         * @brief Get AutoZero enable state.
         * @return bool true if AutoZero is enabled.
         * @note Reads register 0, bit 7.
         */
        bool getAutoZero() const;

        /**
         * @brief Set main loudness attenuation (0-15).
         * @param attenuation attenuation value [0..15].
         * @note Affects register 1, bits [3:0].
         */
        void setLoudnessAttenuation(uint8_t attenuation);
        /**
         * @brief Get main loudness attenuation.
         * @return uint8_t attenuation [0..15].
         * @note Reads register 1, bits [3:0].
         */
        uint8_t getLoudnessAttenuation() const;

        /**
         * @brief Set loudness center frequency.
         * @param freq LoudnessCenterFreq enum value.
         * @note Affects register 1, bits [5:4].
         */
        void setLoudnessCenterFreq(LoudnessCenterFreq freq);
        /**
         * @brief Get loudness center frequency.
         * @return LoudnessCenterFreq current selection.
         * @note Reads register 1, bits [5:4].
         */
        LoudnessCenterFreq getLoudnessCenterFreq() const;

        /**
         * @brief Enable or disable loudness high boost.
         * @param enable true to enable high boost.
         * @note Affects register 1, bit 6.
         */
        void setLoudnessHighBoost(bool enable);
        /**
         * @brief Get loudness high boost state.
         * @return bool true if high boost enabled.
         * @note Reads register 1, bit 6.
         */
        bool getLoudnessHighBoost() const;

        /**
         * @brief Enable or disable loudness soft-step.
         * @param enable true to enable soft-step.
         * @note Affects register 1, bit 7.
         */
        void setLoudnessSoftStep(bool enable);
        /**
         * @brief Get loudness soft-step enable state.
         * @return bool true if soft-step enabled.
         * @note Reads register 1, bit 7.
         */
        bool getLoudnessSoftStep() const;

        /**
         * @brief Enable or disable soft-mute.
         * @param enable true to enable soft-mute.
         * @note Affects register 2, bit 0.
         */
        void setSoftMute(bool enable);
        /**
         * @brief Get soft-mute enable state.
         * @return bool true if soft-mute enabled.
         * @note Reads register 2, bit 0.
         */
        bool getSoftMute() const;

        /**
         * @brief Enable or disable mute pin functionality.
         * @param enable true to enable mute-pin.
         * @note Affects register 2, bit 1.
         */
        void setMutePinEnable(bool enable);
        /**
         * @brief Get mute-pin enable state.
         * @return bool true if mute-pin enabled.
         * @note Reads register 2, bit 1.
         */
        bool getMutePinEnable() const;

        /**
         * @brief Set soft-mute time.
         * @param time SoftMuteTime enum value.
         * @note Affects register 2, bits [3:2].
         */
        void setSoftMuteTime(SoftMuteTime time);
        /**
         * @brief Get soft-mute time selection.
         * @return SoftMuteTime current selection.
         * @note Reads register 2, bits [3:2].
         */
        SoftMuteTime getSoftMuteTime() const;

        /**
         * @brief Set soft-step time.
         * @param time SoftStepTime enum value.
         * @note Affects register 2, bits [6:4].
         */
        void setSoftStepTime(SoftStepTime time);
        /**
         * @brief Get soft-step time selection.
         * @return SoftStepTime current selection.
         * @note Reads register 2, bits [6:4].
         */
        SoftStepTime getSoftStepTime() const;

        /**
         * @brief Enable or disable fast clock mode.
         * @param enable true to enable fast clock mode.
         * @note Affects register 2, bit 7.
         */
        void setClockFastMode(bool enable);
        /**
         * @brief Get fast clock mode state.
         * @return bool true if fast clock mode enabled.
         * @note Reads register 2, bit 7.
         */
        bool getClockFastMode() const;

        /**
         * @brief Enable or disable master volume soft-step.
         * @param enable true to enable master volume soft-step.
         * @note Affects register 3, bit 7.
         */
        void setMasterVolumeSoftStep(bool enable);
        /**
         * @brief Get master volume soft-step state.
         * @return bool true if enabled.
         * @note Reads register 3, bit 7.
         */
        bool getMasterVolumeSoftStep() const;

        /**
         * @brief Set master volume attenuation (7-bit).
         * @param volume Volume in range [-80..+15] encoded by driver as 7-bit register value.
         * @note Affects register 3, bits [6:0].
         */
        void setMasterVolume(int8_t volume);
        /**
         * @brief Get master volume attenuation.
         * @return int8_t volume in dB-equivalent range [-80..+15].
         * @note Reads register 3, bits [6:0].
         */
        int8_t getMasterVolume() const;

        /**
         * @brief Set treble EQ level (-15..+15).
         * @param level Treble level in steps; driver converts to register encoding.
         * @note Affects register 4, bits [4:0].
         */
        void setTrebleLevel(int8_t level);
        /**
         * @brief Get treble EQ level.
         * @return int8_t level in range [-15..+15].
         * @note Reads register 4, bits [4:0].
         */
        int8_t getTrebleLevel() const;

        /**
         * @brief Set treble center frequency.
         * @param freq TrebleCenterFreq enum value.
         * @note Affects register 4, bits [6:5].
         */
        void setTrebleCenterFreq(TrebleCenterFreq freq);
        /**
         * @brief Get treble center frequency.
         * @return TrebleCenterFreq current selection.
         * @note Reads register 4, bits [6:5].
         */
        TrebleCenterFreq getTrebleCenterFreq() const;

        /**
         * @brief Select internal/external treble reference.
         * @param useInternal true to select internal reference.
         * @note Affects register 4, bit 7.
         */
        void setTrebleReferenceInternal(bool useInternal);
        /**
         * @brief Get treble reference selection.
         * @return bool true if internal reference selected.
         * @note Reads register 4, bit 7.
         */
        bool getTrebleReferenceInternal() const;

        /**
         * @brief Enable or disable middle filter soft-step.
         * @param enable true to enable.
         * @note Affects register 5, bit 7.
         */
        void setMiddleSoftStep(bool enable);
        /**
         * @brief Get middle soft-step enable state.
         * @return bool true if enabled.
         * @note Reads register 5, bit 7.
         */
        bool getMiddleSoftStepEnabled() const;

        /**
         * @brief Set middle EQ level (-15..+15).
         * @param level Level in steps.
         * @note Affects register 5, bits [4:0].
         */
        void setMiddleLevel(int8_t level);
        /**
         * @brief Get middle EQ level.
         * @return int8_t level [-15..+15].
         * @note Reads register 5, bits [4:0].
         */
        int8_t getMiddleLevel() const;

        /**
         * @brief Set middle Q factor.
         * @param q MiddleQFactor enum value.
         * @note Affects register 5, bits [6:5].
         */
        void setMiddleQFactor(MiddleQFactor q);
        /**
         * @brief Get middle Q factor.
         * @return MiddleQFactor current selection.
         * @note Reads register 5, bits [6:5].
         */
        MiddleQFactor getMiddleQFactor() const;

        /**
         * @brief Enable or disable bass soft-step.
         * @param enable true to enable.
         * @note Affects register 6, bit 7.
         */
        void setBassSoftStep(bool enable);
        /**
         * @brief Get bass soft-step enable state.
         * @return bool true if enabled.
         * @note Reads register 6, bit 7.
         */
        bool getBassSoftStep() const;

        /**
         * @brief Set bass EQ level (-15..+15).
         * @param level Level in steps.
         * @note Affects register 6, bits [4:0].
         */
        void setBassLevel(int8_t level);
        /**
         * @brief Get bass EQ level.
         * @return int8_t level [-15..+15].
         * @note Reads register 6, bits [4:0].
         */
        int8_t getBassLevel() const;

        /**
         * @brief Set bass Q factor.
         * @param q BassQFactor enum value.
         * @note Affects register 6, bits [6:5].
         */
        void setBassQFactor(BassQFactor q);
        /**
         * @brief Get bass Q factor.
         * @return BassQFactor current selection.
         * @note Reads register 6, bits [6:5].
         */
        BassQFactor getBassQFactor() const;

        /**
         * @brief Enable or disable smoothing filter.
         * @param enable true to enable smoothing filter.
         * @note Affects register 8, bit 7.
         */
        void setSmoothingFilter(bool enable);
        /**
         * @brief Get smoothing filter enable state.
         * @return bool true if enabled.
         * @note Reads register 8, bit 7.
         */
        bool getSmoothingFilter() const;

        /**
         * @brief Enable or disable bass DC mode.
         * @param enable true to enable bass DC mode.
         * @note Affects register 8, bit 6.
         */
        void setBassDcMode(bool enable);
        /**
         * @brief Get bass DC mode state.
         * @return bool true if enabled.
         * @note Reads register 8, bit 6.
         */
        bool getBassDcMode() const;

        /**
         * @brief Set bass center frequency.
         * @param freq BassCenterFreq enum value.
         * @note Affects register 8, bits [5:4].
         */
        void setBassCenterFreq(BassCenterFreq freq);
        /**
         * @brief Get bass center frequency.
         * @return BassCenterFreq current selection.
         * @note Reads register 8, bits [5:4].
         */
        BassCenterFreq getBassCenterFreq() const;

        /**
         * @brief Set middle center frequency.
         * @param freq MiddleCenterFreq enum value.
         * @note Affects register 8, bits [3:2].
         */
        void setMiddleCenterFreq(MiddleCenterFreq freq);
        /**
         * @brief Get middle center frequency.
         * @return MiddleCenterFreq current selection.
         * @note Reads register 8, bits [3:2].
         */
        MiddleCenterFreq getMiddleCenterFreq() const;

        /**
         * @brief Set subwoofer cutoff frequency.
         * @param freq SubCutoffFreq enum value.
         * @note Affects register 8, bits [1:0].
         */
        void setSubCutoffFreq(SubCutoffFreq freq);
        /**
         * @brief Get subwoofer cutoff frequency.
         * @return SubCutoffFreq current selection.
         * @note Reads register 8, bits [1:0].
         */
        SubCutoffFreq getSubCutoffFreq() const;

        /**
         * @brief Set mixing gain effect (HPF filter gain).
         * @param effect MixingGainEffect enum value.
         * @note Affects register 9, bits [7:4].
         */
        void setMixingGainEffect(MixingGainEffect effect);
        /**
         * @brief Get mixing gain effect.
         * @return MixingGainEffect current selection.
         * @note Reads register 9, bits [7:4].
         */
        MixingGainEffect getMixingGainEffect() const;

        /**
         * @brief Enable or disable subwoofer output.
         * @param enable true to enable subwoofer.
         * @note Affects register 9, bit 3.
         */
        void setSubwooferEnable(bool enable);
        /**
         * @brief Get subwoofer enable state.
         * @return bool true if enabled.
         * @note Reads register 9, bit 3.
         */
        bool getSubwooferEnable() const;

        /**
         * @brief Enable or disable mixing.
         * @param enable true to enable mixing.
         * @note Affects register 9, bit 2.
         */
        void setMixingEnable(bool enable);
        /**
         * @brief Get mixing enable state.
         * @return bool true if enabled.
         * @note Reads register 9, bit 2.
         */
        bool getMixingEnable() const;

        /**
         * @brief Route mix to right front speaker.
         * @param enable true to route mix to right front.
         * @note Affects register 9, bit 1.
         */
        void setMixToRightFront(bool enable);
        /**
         * @brief Get mix-to-right-front routing state.
         * @return bool true if routed to right front.
         * @note Reads register 9, bit 1.
         */
        bool getMixToRightFront() const;

        /**
         * @brief Route mix to left front speaker.
         * @param enable true to route mix to left front.
         * @note Affects register 9, bit 0.
         */
        void setMixToLeftFront(bool enable);
        /**
         * @brief Get mix-to-left-front routing state.
         * @return bool true if routed to left front.
         * @note Reads register 9, bit 0.
         */
        bool getMixToLeftFront() const;

        /**
         * @brief Enable or disable speaker soft-step for a channel.
         * @param channel SpeakerChannel to configure.
         * @param enable true to enable soft-step for the channel.
         * @note Affects register (10 + channel), bit 7.
         */
        void setSpeakerSoftStep(SpeakerChannel channel, bool enable);
        /**
         * @brief Get speaker soft-step enable state for a channel.
         * @param channel SpeakerChannel to query.
         * @return bool true if soft-step enabled for the channel.
         * @note Reads register (10 + channel), bit 7.
         */
        bool getSpeakerSoftStep(SpeakerChannel channel) const;

        /**
         * @brief Set speaker volume for a channel (7-bit).
         * @param channel SpeakerChannel to configure.
         * @param volume int8_t volume encoded by driver as 7-bit register value.
         * @note Affects register (10 + channel), bits [6:0].
         */
        void setSpeakerVolume(SpeakerChannel channel, int8_t volume);
        /**
         * @brief Get speaker volume for a channel.
         * @param channel SpeakerChannel to query.
         * @return int8_t volume in driver scale.
         * @note Reads register (10 + channel), bits [6:0].
         */
        int8_t getSpeakerVolume(SpeakerChannel channel) const;

        /**
         * @brief Enable or disable mixing channel soft-step.
         * @param enable true to enable soft-step.
         * @note Affects register 14, bit 7.
         */
        void setMixingChannelSoftStep(bool enable);
        /**
         * @brief Get mixing channel soft-step enable state.
         * @return bool true if enabled.
         * @note Reads register 14, bit 7.
         */
        bool getMixingChannelSoftStep() const;

        /**
         * @brief Set mixing channel volume (-80..+15).
         * @param volume int8_t volume in dB-equivalent; driver converts to the 7-bit register value.
         * @note Affects register 14, bits [6:0].
         */
        void setMixingChannelVolume(int8_t volume);
        /**
         * @brief Get mixing channel volume.
         * @return int8_t volume in driver scale [-80..+15].
         * @note Reads register 14, bits [6:0].
         */
        int8_t getMixingChannelVolume() const;

        /**
         * @brief Enable or disable subwoofer soft-step.
         * @param enable true to enable soft-step.
         * @note Affects register 15, bit 7.
         */
        void setSubwooferSoftStep(bool enable);
        /**
         * @brief Get subwoofer soft-step enable state.
         * @return bool true if enabled.
         * @note Reads register 15, bit 7.
         */
        bool getSubwooferSoftStep() const;

        /**
         * @brief Set subwoofer volume (-80..+15).
         * @param volume int8_t volume in driver scale.
         * @note Affects register 15, bits [6:0].
         */
        void setSubwooferVolume(int8_t volume);
        /**
         * @brief Get subwoofer volume.
         * @return int8_t volume in driver scale [-80..+15].
         * @note Reads register 15, bits [6:0].
         */
        int8_t getSubwooferVolume() const;

        /**
         * @brief Set spectrum analyzer coupling mode.
         * @param mode SpectrumCouplingMode enum value.
         * @note Affects register 16, bits [7:6].
         */
        void setSpectrumCouplingMode(SpectrumCouplingMode mode);
        /**
         * @brief Get spectrum analyzer coupling mode.
         * @return SpectrumCouplingMode current selection.
         * @note Reads register 16, bits [7:6].
         */
        SpectrumCouplingMode getSpectrumCouplingMode() const;

        /**
         * @brief Select external clock source.
         * @param useExternal true to use external clock.
         * @note Affects register 16, bit 5.
         */
        void setExternalClock(bool useExternal);
        /**
         * @brief Get external clock selection.
         * @return bool true if external clock selected.
         * @note Reads register 16, bit 5.
         */
        bool getExternalClock() const;

        /**
         * @brief Trigger spectrum reset.
         * @param enable true to set the spectrum reset bit (self-clearing as per chip behaviour).
         * @note Affects register 16, bit 4.
         */
        void setSpectrumReset(bool enable);
        /**
         * @brief Get spectrum reset state (if readable).
         * @return bool true if spectrum reset bit set.
         * @note Reads register 16, bit 4.
         */
        bool getSpectrumReset() const;

        /**
         * @brief Start/stop spectrum analyzer run.
         * @param enable true to run spectrum analyzer.
         * @note Affects register 16, bit 3.
         */
        void setSpectrumRun(bool enable);
        /**
         * @brief Get spectrum run state.
         * @return bool true if running.
         * @note Reads register 16, bit 3.
         */
        bool getSpectrumRun() const;

        /**
         * @brief Set spectrum source.
         * @param source SpectrumSource enum value.
         * @note Affects register 16, bit 2.
         */
        void setSpectrumSource(SpectrumSource source);
        /**
         * @brief Get spectrum source.
         * @return SpectrumSource current selection.
         * @note Reads register 16, bit 2.
         */
        SpectrumSource getSpectrumSource() const;

        /**
         * @brief Enable or disable spectrum auto-reset.
         * @param enable true to enable auto-reset.
         * @note Affects register 16, bit 1.
         */
        void setSpectrumAutoReset(bool enable);
        /**
         * @brief Get spectrum auto-reset enable state.
         * @return bool true if enabled.
         * @note Reads register 16, bit 1.
         */
        bool getSpectrumAutoReset() const;

        /**
         * @brief Set spectrum filter Q.
         * @param filterQ SpectrumFilterQ enum value.
         * @note Affects register 16, bit 0.
         */
        void setSpectrumFilterQ(SpectrumFilterQ filterQ);
        /**
         * @brief Get spectrum filter Q.
         * @return SpectrumFilterQ current selection.
         * @note Reads register 16, bit 0.
         */
        SpectrumFilterQ getSpectrumFilterQ() const;

        /**
         * @brief Send the entire cached register map to the device.
         * @return bool true on success.
         * @note Writes registers 0..(REGISTER_COUNT-1).
         */
        bool sendAllRegisters();

        /**
         * @brief Send only registers that have changed since last transmission.
         * @return bool true on success.
         * @note Optimizes I2C traffic by using internal changed-flag bookkeeping.
         */
        bool sendChangedRegisters();

        /**
         * @brief Print register contents to the configured debug output if enabled.
         */
        void printRegistersDebug() const;

    private:
        // I2C interface used to communicate with the device
        TwoWire& i2c;


        std::array<bitStorage, REGISTER_COUNT> registers;

        /**
         * @brief Convert user-level volume (dB-equivalent) to 7-bit register encoding.
         * @param volume int8_t user volume in range [-80..+15].
         * @return uint8_t register encoded value to be written to the device (7-bit).
         * @note Used for registers 3, 10..15, 14..15 depending on caller.
         */
        uint8_t convertVolumeToRegisterValue(int8_t volume) const;
        /**
         * @brief Convert a 7-bit register value to user-level volume.
         * @param regValue uint8_t raw register value.
         * @return int8_t user-visible volume in range [-80..+15].
         */
        int8_t convertRegisterValueToVolume(uint8_t regValue) const;

        /**
         * @brief Convert user EQ level (-15..+15) to register encoding.
         * @param gain int8_t EQ gain.
         * @return uint8_t register encoded value.
         * @note Used for EQ registers 4,5,6.
         */
        uint8_t convertEQLevelToRegisterValue(int8_t gain) const;
        /**
         * @brief Convert EQ register value to signed level.
         * @param regValue uint8_t raw register value.
         * @return int8_t signed EQ level [-15..+15].
         */
        int8_t convertRegisterValueToEQLevel(uint8_t regValue) const;

        /**
         * @brief Print I2C transmission error details for debugging.
         * @param errorCode I2C error code from Wire.endTransmission.
         */
        void printTransmissionError(uint8_t errorCode) const;

        bool inputChanged = true;

    };

} // namespace TDA7419