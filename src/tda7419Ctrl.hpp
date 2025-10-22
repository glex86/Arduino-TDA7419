#pragma once

#include "tda7419.hpp"

namespace TDA7419 {

	/**
	 * @brief Adapter providing nested short-call interfaces (e.g. adapter.treble.setCenterFreq(...)).
	 * @details Each nested group forwards calls to the underlying TDA7419 instance.
	 */
	class TDA7419Ctrl {
	private:
		TDA7419& dev;
	public:
		/**
		 * @brief Construct the controller adapter from an existing device instance.
		 * @param device Reference to an initialized TDA7419 device object.
		 */
		explicit TDA7419Ctrl(TDA7419& device) : dev(device), treble(*this), bass(*this),
			middle(*this), volume(*this), loudness(*this), input(*this),
			mixing(*this), spectrum(*this), speaker(*this), subwoofer(*this), system(*this), i2c(*this) {
		}

		// Treble group
		struct Treble {
			TDA7419Ctrl& parent;
			explicit Treble(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set treble center frequency.
			 * @param f TrebleCenterFreq enum value.
			 * @note Affects register 4, bits [6:5].
			 */
			void setCenterFreq(TrebleCenterFreq f) { parent.dev.setTrebleCenterFreq(f); }

			/**
			 * @brief Get treble center frequency.
			 * @return TrebleCenterFreq current selection.
			 * @note Reads register 4, bits [6:5].
			 */
			TrebleCenterFreq getCenterFreq() const { return parent.dev.getTrebleCenterFreq(); }

			/**
			 * @brief Set treble gain level.
			 * @param g int8_t level in range [-15..+15].
			 * @note Affects register 4, bits [4:0].
			 */
			void setGain(int8_t g) { parent.dev.setTrebleLevel(g); }

			/**
			 * @brief Get treble gain level.
			 * @return int8_t level in range [-15..+15].
			 * @note Reads register 4, bits [4:0].
			 */
			int8_t getGain() const { return parent.dev.getTrebleLevel(); }

			/**
			 * @brief Select internal/external treble reference.
			 * @param v true to select internal reference.
			 * @note Affects register 4, bit 7.
			 */
			void setReferenceInternal(bool v) { parent.dev.setTrebleReferenceInternal(v); }

			/**
			 * @brief Get treble reference selection.
			 * @return bool true if internal reference selected.
			 * @note Reads register 4, bit 7.
			 */
			bool getReferenceInternal() const { return parent.dev.getTrebleReferenceInternal(); }
		};

		// Bass group
		struct Bass {
			TDA7419Ctrl& parent;
			explicit Bass(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set bass center frequency.
			 * @param f BassCenterFreq enum value.
			 * @note Affects register 8, bits [5:4].
			 */
			void setCenterFreq(BassCenterFreq f) { parent.dev.setBassCenterFreq(f); }

			/**
			 * @brief Get bass center frequency.
			 * @return BassCenterFreq current selection.
			 * @note Reads register 8, bits [5:4].
			 */
			BassCenterFreq getCenterFreq() const { return parent.dev.getBassCenterFreq(); }

			/**
			 * @brief Set bass gain level.
			 * @param g int8_t level in range [-15..+15].
			 * @note Affects register 6, bits [4:0].
			 */
			void setGain(int8_t g) { parent.dev.setBassLevel(g); }

			/**
			 * @brief Get bass gain level.
			 * @return int8_t level in range [-15..+15].
			 * @note Reads register 6, bits [4:0].
			 */
			int8_t getGain() const { return parent.dev.getBassLevel(); }

			/**
			 * @brief Set bass Q factor.
			 * @param q BassQFactor enum value.
			 * @note Affects register 6, bits [6:5].
			 */
			void setQ(BassQFactor q) { parent.dev.setBassQFactor(q); }

			/**
			 * @brief Get bass Q factor.
			 * @return BassQFactor current selection.
			 * @note Reads register 6, bits [6:5].
			 */
			BassQFactor getQ() const { return parent.dev.getBassQFactor(); }

			/**
			 * @brief Enable or disable bass DC mode.
			 * @param v true to enable bass DC mode.
			 * @note Affects register 8, bit 6.
			 */
			void setDcMode(bool v) { parent.dev.setBassDcMode(v); }

			/**
			 * @brief Get bass DC mode state.
			 * @return bool true if enabled.
			 * @note Reads register 8, bit 6.
			 */
			bool getDcMode() const { return parent.dev.getBassDcMode(); }

			/**
			 * @brief Enable or disable bass soft-step.
			 * @param v true to enable.
			 * @note Affects register 6, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setBassSoftStep(v); }

			/**
			 * @brief Get bass soft-step enable state.
			 * @return bool true if enabled.
			 * @note Reads register 6, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getBassSoftStep(); }
		};

		// Middle group
		struct Middle {
			TDA7419Ctrl& parent;
			explicit Middle(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set middle center frequency.
			 * @param f MiddleCenterFreq enum value.
			 * @note Affects register 8, bits [3:2].
			 */
			void setCenterFreq(MiddleCenterFreq f) { parent.dev.setMiddleCenterFreq(f); }

			/**
			 * @brief Get middle center frequency.
			 * @return MiddleCenterFreq current selection.
			 * @note Reads register 8, bits [3:2].
			 */
			MiddleCenterFreq getCenterFreq() const { return parent.dev.getMiddleCenterFreq(); }

			/**
			 * @brief Set middle gain level.
			 * @param g int8_t level in range [-15..+15].
			 * @note Affects register 5, bits [4:0].
			 */
			void setGain(int8_t g) { parent.dev.setMiddleLevel(g); }

			/**
			 * @brief Get middle gain level.
			 * @return int8_t level in range [-15..+15].
			 * @note Reads register 5, bits [4:0].
			 */
			int8_t getGain() const { return parent.dev.getMiddleLevel(); }

			/**
			 * @brief Set middle Q factor.
			 * @param q MiddleQFactor enum value.
			 * @note Affects register 5, bits [6:5].
			 */
			void setQ(MiddleQFactor q) { parent.dev.setMiddleQFactor(q); }

			/**
			 * @brief Get middle Q factor.
			 * @return MiddleQFactor current selection.
			 * @note Reads register 5, bits [6:5].
			 */
			MiddleQFactor getQ() const { return parent.dev.getMiddleQFactor(); }

			/**
			 * @brief Enable or disable middle filter soft-step.
			 * @param v true to enable.
			 * @note Affects register 5, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setMiddleSoftStep(v); }

			/**
			 * @brief Get middle soft-step enable state.
			 * @return bool true if enabled.
			 * @note Reads register 5, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getMiddleSoftStepEnabled(); }
		};

		// Volume / master
		struct Volume {
			TDA7419Ctrl& parent;
			explicit Volume(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set master volume attenuation (7-bit).
			 * @param a int8_t volume in range [-80..+15].
			 * @note Affects register 3, bits [6:0].
			 */
			void set(int8_t a) { parent.dev.setMasterVolume(a); }

			/**
			 * @brief Get master volume attenuation.
			 * @return int8_t volume in dB-equivalent range [-80..+15].
			 * @note Reads register 3, bits [6:0].
			 */
			int8_t get() const { return parent.dev.getMasterVolume(); }

			/**
			 * @brief Enable or disable master volume soft-step.
			 * @param v true to enable soft-step.
			 * @note Affects register 3, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setMasterVolumeSoftStep(v); }

			/**
			 * @brief Get master volume soft-step state.
			 * @return bool true if enabled.
			 * @note Reads register 3, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getMasterVolumeSoftStep(); }
		};

		// Loudness group
		struct Loudness {
			TDA7419Ctrl& parent;
			explicit Loudness(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set main loudness attenuation (0-15).
			 * @param a attenuation value [0..15].
			 * @note Affects register 1, bits [3:0].
			 */
			void setAttenuation(uint8_t a) { parent.dev.setLoudnessAttenuation(a); }

			/**
			 * @brief Get main loudness attenuation.
			 * @return uint8_t attenuation [0..15].
			 * @note Reads register 1, bits [3:0].
			 */
			uint8_t getAttenuation() const { return parent.dev.getLoudnessAttenuation(); }

			/**
			 * @brief Set loudness center frequency.
			 * @param f LoudnessCenterFreq enum value.
			 * @note Affects register 1, bits [5:4].
			 */
			void setCenterFreq(LoudnessCenterFreq f) { parent.dev.setLoudnessCenterFreq(f); }

			/**
			 * @brief Get loudness center frequency.
			 * @return LoudnessCenterFreq current selection.
			 * @note Reads register 1, bits [5:4].
			 */
			LoudnessCenterFreq getCenterFreq() const { return parent.dev.getLoudnessCenterFreq(); }

			/**
			 * @brief Enable or disable loudness high boost.
			 * @param v true to enable high boost.
			 * @note Affects register 1, bit 6.
			 */
			void setHighBoost(bool v) { parent.dev.setLoudnessHighBoost(v); }

			/**
			 * @brief Get loudness high boost state.
			 * @return bool true if high boost enabled.
			 * @note Reads register 1, bit 6.
			 */
			bool getHighBoost() const { return parent.dev.getLoudnessHighBoost(); }

			/**
			 * @brief Enable or disable loudness soft-step.
			 * @param v true to enable soft-step.
			 * @note Affects register 1, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setLoudnessSoftStep(v); }

			/**
			 * @brief Get loudness soft-step enable state.
			 * @return bool true if soft-step enabled.
			 * @note Reads register 1, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getLoudnessSoftStep(); }
		};

		// Input / source group
		struct Input {
			TDA7419Ctrl& parent;
			explicit Input(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set the main input source.
			 * @param s InputSource enum value to select.
			 * @note Affects register 0, bits [2:0].
			 */
			void setMainSource(InputSource s) { parent.dev.setMainSource(s); }

			/**
			 * @brief Get the current main input source.
			 * @return InputSource current selection.
			 * @note Reads register 0, bits [2:0].
			 */
			InputSource getMainSource() const { return parent.dev.getMainSource(); }

			/**
			 * @brief Set the main input gain (0-15).
			 * @param g Gain value in range [0..15].
			 * @note Affects register 0, bits [6:3].
			 */
			void setInputGain(uint8_t g) { parent.dev.setInputGain(g); }

			/**
			 * @brief Get the current main input gain.
			 * @return uint8_t gain in range [0..15].
			 * @note Reads register 0, bits [6:3].
			 */
			uint8_t getInputGain() const { return parent.dev.getInputGain(); }

			/**
			 * @brief Set the second input source selection.
			 * @param s InputSource enum value.
			 * @note Affects register 7, bits [2:0].
			 */
			void setSecondSource(InputSource s) { parent.dev.setSecondSource(s); }

			/**
			 * @brief Get the second input source selection.
			 * @return InputSource current selection.
			 * @note Reads register 7, bits [2:0].
			 */
			InputSource getSecondSource() const { return parent.dev.getSecondSource(); }

			/**
			 * @brief Set the second source input gain (0-15).
			 * @param g Gain value [0..15].
			 * @note Affects register 7, bits [6:3].
			 */
			void setSecondSourceGain(uint8_t g) { parent.dev.setSecondSourceInputGain(g); }

			/**
			 * @brief Get the second source input gain.
			 * @return uint8_t gain [0..15].
			 * @note Reads register 7, bits [6:3].
			 */
			uint8_t getSecondSourceGain() const { return parent.dev.getSecondSourceInputGain(); }

			/**
			 * @brief Set the rear speaker source selection.
			 * @param s RearSpeakerSource enum value.
			 * @note Affects register 7, bit 7.
			 */
			void setRearSpeakerSource(RearSpeakerSource s) { parent.dev.setRearSpeakerSource(s); }

			/**
			 * @brief Get the rear speaker source selection.
			 * @return RearSpeakerSource current selection.
			 * @note Reads register 7, bit 7.
			 */
			RearSpeakerSource getRearSpeakerSource() const { return parent.dev.getRearSpeakerSource(); }

			/**
			 * @brief Enable or disable AutoZero.
			 * @param v true to enable AutoZero, false to disable.
			 * @note Affects register 0, bit 7.
			 */
			void setAutoZero(bool v) { parent.dev.setAutoZero(v); }

			/**
			 * @brief Get AutoZero enable state.
			 * @return bool true if AutoZero is enabled.
			 * @note Reads register 0, bit 7.
			 */
			bool getAutoZero() const { return parent.dev.getAutoZero(); }
		};

		// Mixing group
		struct Mixing {
			TDA7419Ctrl& parent;
			explicit Mixing(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set mixing gain effect (HPF filter gain).
			 * @param e MixingGainEffect enum value.
			 * @note Affects register 9, bits [7:4].
			 */
			void setGainEffect(MixingGainEffect e) { parent.dev.setMixingGainEffect(e); }

			/**
			 * @brief Get mixing gain effect.
			 * @return MixingGainEffect current selection.
			 * @note Reads register 9, bits [7:4].
			 */
			MixingGainEffect getGainEffect() const { return parent.dev.getMixingGainEffect(); }

			/**
			 * @brief Enable or disable mixing.
			 * @param v true to enable mixing.
			 * @note Affects register 9, bit 2.
			 */
			void setEnable(bool v) { parent.dev.setMixingEnable(v); }

			/**
			 * @brief Get mixing enable state.
			 * @return bool true if enabled.
			 * @note Reads register 9, bit 2.
			 */
			bool getEnable() const { return parent.dev.getMixingEnable(); }

			/**
			 * @brief Route mix to left front speaker.
			 * @param v true to route mix to left front.
			 * @note Affects register 9, bit 0.
			 */
			void setToLeftFront(bool v) { parent.dev.setMixToLeftFront(v); }

			/**
			 * @brief Get mix-to-left-front routing state.
			 * @return bool true if routed to left front.
			 * @note Reads register 9, bit 0.
			 */
			bool getToLeftFront() const { return parent.dev.getMixToLeftFront(); }

			/**
			 * @brief Route mix to right front speaker.
			 * @param v true to route mix to right front.
			 * @note Affects register 9, bit 1.
			 */
			void setToRightFront(bool v) { parent.dev.setMixToRightFront(v); }

			/**
			 * @brief Get mix-to-right-front routing state.
			 * @return bool true if routed to right front.
			 * @note Reads register 9, bit 1.
			 */
			bool getToRightFront() const { return parent.dev.getMixToRightFront(); }

			/**
			 * @brief Set mixing channel volume (-80..+15).
			 * @param a int8_t volume in dB-equivalent.
			 * @note Affects register 14, bits [6:0].
			 */
			void setVolume(int8_t a) { parent.dev.setMixingChannelVolume(a); }

			/**
			 * @brief Get mixing channel volume.
			 * @return int8_t volume in driver scale [-80..+15].
			 * @note Reads register 14, bits [6:0].
			 */
			int8_t getVolume() const { return parent.dev.getMixingChannelVolume(); }

			/**
			 * @brief Enable or disable mixing channel soft-step.
			 * @param v true to enable soft-step.
			 * @note Affects register 14, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setMixingChannelSoftStep(v); }

			/**
			 * @brief Get mixing channel soft-step enable state.
			 * @return bool true if enabled.
			 * @note Reads register 14, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getMixingChannelSoftStep(); }
		};

		// Spectrum group
		struct Spectrum {
			TDA7419Ctrl& parent;
			explicit Spectrum(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set spectrum analyzer coupling mode.
			 * @param m SpectrumCouplingMode enum value.
			 * @note Affects register 16, bits [7:6].
			 */
			void setCouplingMode(SpectrumCouplingMode m) { parent.dev.setSpectrumCouplingMode(m); }

			/**
			 * @brief Get spectrum analyzer coupling mode.
			 * @return SpectrumCouplingMode current selection.
			 * @note Reads register 16, bits [7:6].
			 */
			SpectrumCouplingMode getCouplingMode() const { return parent.dev.getSpectrumCouplingMode(); }

			/**
			 * @brief Start/stop spectrum analyzer run.
			 * @param v true to run spectrum analyzer.
			 * @note Affects register 16, bit 3.
			 */
			void setRun(bool v) { parent.dev.setSpectrumRun(v); }

			/**
			 * @brief Get spectrum run state.
			 * @return bool true if running.
			 * @note Reads register 16, bit 3.
			 */
			bool getRun() const { return parent.dev.getSpectrumRun(); }

			/**
			 * @brief Set spectrum source.
			 * @param s SpectrumSource enum value.
			 * @note Affects register 16, bit 2.
			 */
			void setSource(SpectrumSource s) { parent.dev.setSpectrumSource(s); }

			/**
			 * @brief Get spectrum source.
			 * @return SpectrumSource current selection.
			 * @note Reads register 16, bit 2.
			 */
			SpectrumSource getSource() const { return parent.dev.getSpectrumSource(); }

			/**
			 * @brief Set spectrum filter Q.
			 * @param q SpectrumFilterQ enum value.
			 * @note Affects register 16, bit 0.
			 */
			void setFilterQ(SpectrumFilterQ q) { parent.dev.setSpectrumFilterQ(q); }

			/**
			 * @brief Get spectrum filter Q.
			 * @return SpectrumFilterQ current selection.
			 * @note Reads register 16, bit 0.
			 */
			SpectrumFilterQ getFilterQ() const { return parent.dev.getSpectrumFilterQ(); }

			/**
			 * @brief Enable or disable spectrum auto-reset.
			 * @param v true to enable auto-reset.
			 * @note Affects register 16, bit 1.
			 */
			void setAutoReset(bool v) { parent.dev.setSpectrumAutoReset(v); }

			/**
			 * @brief Get spectrum auto-reset enable state.
			 * @return bool true if enabled.
			 * @note Reads register 16, bit 1.
			 */
			bool getAutoReset() const { return parent.dev.getSpectrumAutoReset(); }

			/**
			 * @brief Trigger spectrum reset.
			 * @param v true to set the spectrum reset bit (self-clearing as per chip behaviour).
			 * @note Affects register 16, bit 4.
			 */
			void setReset(bool v) { parent.dev.setSpectrumReset(v); }

			/**
			 * @brief Get spectrum reset state (if readable).
			 * @return bool true if spectrum reset bit set.
			 * @note Reads register 16, bit 4.
			 */
			bool getReset() const { return parent.dev.getSpectrumReset(); }

			/**
			 * @brief Select external clock source.
			 * @param v true to use external clock.
			 * @note Affects register 16, bit 5.
			 */
			void setExternalClock(bool v) { parent.dev.setExternalClock(v); }

			/**
			 * @brief Get external clock selection.
			 * @return bool true if external clock selected.
			 * @note Reads register 16, bit 5.
			 */
			bool getExternalClock() const { return parent.dev.getExternalClock(); }
		};

		// Speaker group (per-channel methods)
		struct Speaker {
			TDA7419Ctrl& parent;
			explicit Speaker(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Enable or disable speaker soft-step for a channel.
			 * @param ch SpeakerChannel to configure.
			 * @param v true to enable soft-step for the channel.
			 * @note Affects register (10 + channel), bit 7.
			 */
			void setSoftStep(SpeakerChannel ch, bool v) { parent.dev.setSpeakerSoftStep(ch, v); }

			/**
			 * @brief Get speaker soft-step enable state for a channel.
			 * @param ch SpeakerChannel to query.
			 * @return bool true if soft-step enabled for the channel.
			 * @note Reads register (10 + channel), bit 7.
			 */
			bool getSoftStep(SpeakerChannel ch) const { return parent.dev.getSpeakerSoftStep(ch); /* note: original API name */ }

			/**
			 * @brief Set speaker volume for a channel (7-bit).
			 * @param ch SpeakerChannel to configure.
			 * @param a int8_t volume in driver scale.
			 * @note Affects register (10 + channel), bits [6:0].
			 */
			void setVolume(SpeakerChannel ch, int8_t a) { parent.dev.setSpeakerVolume(ch, a); }

			/**
			 * @brief Get speaker volume for a channel.
			 * @param ch SpeakerChannel to query.
			 * @return int8_t volume in driver scale.
			 * @note Reads register (10 + channel), bits [6:0].
			 */
			int8_t getVolume(SpeakerChannel ch) const { return parent.dev.getSpeakerVolume(ch); }
		};

		// Subwoofer group
		struct Subwoofer {
			TDA7419Ctrl& parent;
			explicit Subwoofer(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Set subwoofer volume (-80..+15).
			 * @param a int8_t volume in driver scale.
			 * @note Affects register 15, bits [6:0].
			 */
			void setVolume(int8_t a) { parent.dev.setSubwooferVolume(a); }

			/**
			 * @brief Get subwoofer volume.
			 * @return int8_t volume in driver scale [-80..+15].
			 * @note Reads register 15, bits [6:0].
			 */
			int8_t getVolume() const { return parent.dev.getSubwooferVolume(); }

			/**
			 * @brief Enable or disable subwoofer soft-step.
			 * @param v true to enable soft-step.
			 * @note Affects register 15, bit 7.
			 */
			void setSoftStep(bool v) { parent.dev.setSubwooferSoftStep(v); }

			/**
			 * @brief Get subwoofer soft-step enable state.
			 * @return bool true if enabled.
			 * @note Reads register 15, bit 7.
			 */
			bool getSoftStep() const { return parent.dev.getSubwooferSoftStep(); }

			/**
			 * @brief Enable or disable subwoofer output.
			 * @param v true to enable subwoofer.
			 * @note Affects register 9, bit 3.
			 */
			void setEnable(bool v) { parent.dev.setSubwooferEnable(v); }

			/**
			 * @brief Get subwoofer enable state.
			 * @return bool true if enabled.
			 * @note Reads register 9, bit 3.
			 */
			bool getEnable() const { return parent.dev.getSubwooferEnable(); }

			/**
			 * @brief Set subwoofer cutoff frequency.
			 * @param f SubCutoffFreq enum value.
			 * @note Affects register 8, bits [1:0].
			 */
			void setCutoffFreq(SubCutoffFreq f) { parent.dev.setSubCutoffFreq(f); }

			/**
			 * @brief Get subwoofer cutoff frequency.
			 * @return SubCutoffFreq current selection.
			 * @note Reads register 8, bits [1:0].
			 */
			SubCutoffFreq getCutoffFreq() const { return parent.dev.getSubCutoffFreq(); }
		};

		// System configuration group
		struct System {
			TDA7419Ctrl& parent;
			explicit System(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Enable or disable soft-mute.
			 * @param v true to enable soft-mute.
			 * @note Affects register 2, bit 0.
			 */
			void setSoftMute(bool v) { parent.dev.setSoftMute(v); }

			/**
			 * @brief Get soft-mute enable state.
			 * @return bool true if soft-mute enabled.
			 * @note Reads register 2, bit 0.
			 */
			bool getSoftMute() const { return parent.dev.getSoftMute(); }

			/**
			 * @brief Enable or disable mute pin functionality.
			 * @param v true to enable mute-pin.
			 * @note Affects register 2, bit 1.
			 */
			void setMutePinEnable(bool v) { parent.dev.setMutePinEnable(v); }

			/**
			 * @brief Get mute-pin enable state.
			 * @return bool true if mute-pin enabled.
			 * @note Reads register 2, bit 1.
			 */
			bool getMutePinEnable() const { return parent.dev.getMutePinEnable(); }

			/**
			 * @brief Set soft-mute time.
			 * @param t SoftMuteTime enum value.
			 * @note Affects register 2, bits [3:2].
			 */
			void setSoftMuteTime(SoftMuteTime t) { parent.dev.setSoftMuteTime(t); }

			/**
			 * @brief Get soft-mute time selection.
			 * @return SoftMuteTime current selection.
			 * @note Reads register 2, bits [3:2].
			 */
			SoftMuteTime getSoftMuteTime() const { return parent.dev.getSoftMuteTime(); }

			/**
			 * @brief Set soft-step time.
			 * @param t SoftStepTime enum value.
			 * @note Affects register 2, bits [6:4].
			 */
			void setSoftStepTime(SoftStepTime t) { parent.dev.setSoftStepTime(t); }

			/**
			 * @brief Get soft-step time selection.
			 * @return SoftStepTime current selection.
			 * @note Reads register 2, bits [6:4].
			 */
			SoftStepTime getSoftStepTime() const { return parent.dev.getSoftStepTime(); }

			/**
			 * @brief Enable or disable fast clock mode.
			 * @param v true to enable fast clock mode.
			 * @note Affects register 2, bit 7.
			 */
			void setClockFastMode(bool v) { parent.dev.setClockFastMode(v); }

			/**
			 * @brief Get fast clock mode state.
			 * @return bool true if fast clock mode enabled.
			 * @note Reads register 2, bit 7.
			 */
			bool getClockFastMode() const { return parent.dev.getClockFastMode(); }

			/**
			 * @brief Enable or disable smoothing filter.
			 * @param v true to enable smoothing filter.
			 * @note Affects register 8, bit 7.
			 */
			void setSmoothingFilter(bool v) { parent.dev.setSmoothingFilter(v); }

			/**
			 * @brief Get smoothing filter enable state.
			 * @return bool true if enabled.
			 * @note Reads register 8, bit 7.
			 */
			bool getSmoothingFilter() const { return parent.dev.getSmoothingFilter(); }
		};

		// I2C communication group
		struct I2C {
			TDA7419Ctrl& parent;
			explicit I2C(TDA7419Ctrl& p) : parent(p) {}

			/**
			 * @brief Send the entire cached register map to the device.
			 * @return i2cResult result code of the transmission.
			 * @note Writes registers 0..(REGISTER_COUNT-1).
			 */
			i2cResult sendAllRegisters() { return parent.dev.sendAllRegisters(); }

			/**
			 * @brief Send only registers that have changed since last transmission.
			 * @return i2cResult result code of the transmission.
			 * @note Optimizes I2C traffic by using internal changed-flag bookkeeping.
			 */
			i2cResult sendChangedRegisters() { return parent.dev.sendChangedRegisters(); }

			/**
			 * @brief Send a single register to the device.
			 * @param regIndex Index of the register to send.
			 * @return i2cResult result code of the transmission.
			 */
			i2cResult sendRegister(uint8_t regIndex) { return parent.dev.sendRegister(regIndex); }

			/**
			 * @brief Send arbitrary data to the device over I2C.
			 * @param data Pointer to data buffer.
			 * @param length Length of data in bytes.
			 * @return i2cResult result code of the transmission.
			 */
			i2cResult sendData(const uint8_t* data, size_t length) { return parent.dev.sendData(data, length); }

			/**
			 * @brief Get the value of a specific register.
			 * @param regIndex Index of the register to read.
			 * @return uint8_t value of the register.
			 */
			uint8_t getRegisterValue(uint8_t regIndex) const { return parent.dev.getRegisterValue(regIndex); }

			/**
			 * @brief Set the value of a specific register.
			 * @param regIndex Index of the register to set.
			 * @param value Value to write to the register.
			 */
			void setRegisterValue(uint8_t regIndex, uint8_t value) { parent.dev.setRegisterValue(regIndex, value); }

			/**
			 * @brief Get the sub-address for a register, considering auto-increment and auto-zero settings.
			 * @param regIndex Index of the register.
			 * @param autoIncrement true if auto-increment is enabled.
			 * @param autoZeroRemain true if auto-zero remain is enabled.
			 * @return uint8_t calculated sub-address.
			 */
			uint8_t getSubAddress(uint8_t regIndex, bool autoIncrement, bool autoZeroRemain) const {
				return parent.dev.getSubAddress(regIndex, autoIncrement, autoZeroRemain);
			}

			/**
			 * @brief Print register contents to the configured debug output if enabled.
			 */
			void printRegistersDebug() const { parent.dev.printRegistersDebug(); }
		};

		// Public nested group instances
		Treble treble;
		Bass bass;
		Middle middle;
		Volume volume;
		Loudness loudness;
		Input input;
		Mixing mixing;
		Spectrum spectrum;
		Speaker speaker;
		Subwoofer subwoofer;
		System system;
		I2C i2c;

		// Expose underlying device if needed
		/**
		 * @brief Get reference to underlying TDA7419 device.
		 * @return TDA7419& reference to device.
		 */
		TDA7419& device() { return dev; }

		/**
		 * @brief Initialize the underlying device.
		 * @note Forwards to TDA7419::begin() .
		 */
		void begin() { dev.begin(); }

	};

} // namespace TDA7419
