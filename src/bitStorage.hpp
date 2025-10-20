#pragma once

#include <cstdint>

/**
 * @brief Simple container for an 8-bit register value with bit helpers.
 *
 * This class stores an 8-bit value and provides convenience methods to
 * read/modify individual bits or bit-ranges. It no longer holds a register
 * address — only the value and change-tracking state.
 */
class bitStorage {
public:
    /**
     * @brief Construct a new bitStorage object.
     *
     * The storage does not include an address; it only holds the 8-bit value.
     */
    explicit bitStorage() : value_(0), prevValue_(0) {}

    /**
     * @brief Copy constructor.
     */
    bitStorage(const bitStorage& other) = default;

    /**
     * @brief Copy assignment operator.
     */
    bitStorage& operator=(const bitStorage& other) = default;

    /**
     * @brief Get the stored register value.
     * @return uint8_t The 8-bit register value.
     */
    uint8_t getValue() const { 
        return value_; 
    }

    /**
     * @brief Set the stored register value.
     * @param value The 8-bit value to store.
     */
    void setValue(uint8_t value) { 
        value_ = value;
    }

    /**
     * @brief Set a specific bit in the stored value.
     * @param bitPosition Bit index [0..7] to set to 1.
     */
    void setBit(uint8_t bitPosition) {
        value_ |= (1 << bitPosition);
    }

    /**
     * @brief Clear a specific bit in the stored value.
     * @param bitPosition Bit index [0..7] to clear to 0.
     */
    void clearBit(uint8_t bitPosition) {
        value_ &= ~(1 << bitPosition);
    }

    /**
     * @brief Check whether a specific bit is set.
     * @param bitPosition Bit index [0..7] to query.
     * @return true if the bit is 1, false otherwise.
     */
    bool isBitSet(uint8_t bitPosition) const {
        return (value_ & (1 << bitPosition)) != 0;
    }

    /**
     * @brief Toggle a specific bit in the stored value.
     * @param bitPosition Bit index [0..7] to toggle.
     */
    void toggleBit(uint8_t bitPosition) {
        value_ ^= (1 << bitPosition);
    }

    /**
     * @brief Write a boolean value to a specific bit.
     * @param bitPosition Bit index [0..7] to write.
     * @param value Boolean value to write; true sets the bit, false clears it.
     */
    void writeBit(uint8_t bitPosition, bool value) {
        if (value) {
            setBit(bitPosition);
        }
        else {
            clearBit(bitPosition);
        }
    }

    /**
     * @brief Clear a contiguous segment of bits.
     * @param bitPosition Starting bit index [0..7] of the segment.
     * @param length Number of bits in the segment.
     */
    void clearSegment(uint8_t bitPosition, uint8_t length) {
        if (length == 0 || bitPosition > 7 || (bitPosition + length) > 8) return;
        uint16_t mask = ((uint16_t(1) << length) - 1) << bitPosition;
        value_ &= static_cast<uint8_t>(~mask);
    }

    /**
     * @brief Read a value from a contiguous bit segment.
     * @param bitPosition Starting bit index [0..7] of the segment.
     * @param length Number of bits to read.
     * @return uint8_t Extracted value right-aligned (LSB = segment bitPosition).
     */
    uint8_t readValueAtBit(uint8_t bitPosition, uint8_t length) const {
        if (length == 0 || bitPosition > 7 || (bitPosition + length) > 8) return 0;
        uint16_t mask = ((uint16_t(1) << length) - 1) << bitPosition;
        return static_cast<uint8_t>((value_ & mask) >> bitPosition);
    }

    /**
     * @brief Write a value into a contiguous bit segment.
     * @param bitPosition Starting bit index [0..7] of the segment.
     * @param value Value to write (should fit in 'length' bits).
     * @param length Number of bits in the segment.
     */
    void writeValueAtBit(uint8_t bitPosition, uint8_t value, uint8_t length) {
        if (length == 0 || bitPosition > 7 || (bitPosition + length) > 8) return;
        uint16_t mask = ((uint16_t(1) << length) - 1) << bitPosition;
        value_ = static_cast<uint8_t>((value_ & ~mask) | ((static_cast<uint16_t>(value) << bitPosition) & mask));
    }

    /**
     * @brief Check whether the stored value has changed since the last clearChanged().
     * @return true if the current value differs from the previously saved value.
     */
    bool isChanged() const { 
        return value_ != prevValue_;
    }

    /**
     * @brief Mark the current value as the saved (previous) value, clearing the changed flag.
     */
    void clearChanged() { 
        this->prevValue_ = value_;
    }

private:
    /** @brief Current 8-bit register value. */
    uint8_t value_;
    /** @brief Previously saved value used to detect changes. */
    uint8_t prevValue_;
};
