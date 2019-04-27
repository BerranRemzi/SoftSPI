// Copyright 2019 Berran Remzi
/**
 * @file SoftSPI.h
 * @brief this header file will contain all required
 * definitions and basic utilities functions.
 *
 * @author Berran Remzi
 *
 * @date 07.04.2019
 */
#include "SoftSPI.h"

inline uint8_t SoftSPI_IsInitialized(void) {
    return init_level == ALL_INPUTS_ARE_INITIALIZED;
}

void SoftSPI_InitDelay(uint8_t _dummy_cycles) {
    if (_dummy_cycles > 0) {
        dummy_cycles = _dummy_cycles;
    }
}

void SoftSPI_Init(
    volatile uint8_t * _port,
    uint8_t _data_pin,
    uint8_t _clock_pin,
    uint8_t _latch_pin) {
    SoftSPI_InitDataPin(_port, _data_pin);
    SoftSPI_InitClockPin(_port, _clock_pin);
    SoftSPI_InitLatchPin(_port, _latch_pin);
}

static inline uint8_t convertOutNumberToBit(uint8_t _pin) {
    return 1 << _pin;
}


static inline void SoftSPI_Delay(void) {
    uint8_t _counter = dummy_cycles;
    while ( --_counter != 0)
        continue;
}

void SoftSPI_InitDataPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 0);
    }
    p_data_port = _port;
    data_pin = _pin;
}

void SoftSPI_InitClockPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 1);
    }
    p_clock_port = _port;
    clock_pin = _pin;
}

void SoftSPI_InitLatchPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 2);
    }
    p_latch_port = _port;
    latch_pin = _pin;
}

void SoftSPI_Write(uint8_t _value, uint8_t _bit_order) {
    if (!SoftSPI_IsInitialized()) {
        return;
    }

    for (uint8_t i = 0; i < 8; i++) {
        switch (_bit_order) {
        case SOFT_SPI_MSB_FIRST:
            if ((_value >> i) & 0x01) {
                setBit(p_data_port, data_pin);
            } else {
                clearBit(p_data_port, data_pin);
            }
            break;
        case SOFT_SPI_LSB_FIRST:
            if ((_value << i) & 0x80) {
                setBit(p_data_port, data_pin);
            } else {
                clearBit(p_data_port, data_pin);
            }
            break;
        default: break;
        }
        SoftSPI_ToggleClock();
    }
}

void SoftSPI_Clear(void) {
    SoftSPI_Write(0x00, SOFT_SPI_LSB_FIRST);
}
void setBit(volatile uint8_t * _port, uint8_t _pin) {
    *_port |= convertOutNumberToBit(_pin);
}

void clearBit(volatile uint8_t * _port, uint8_t _pin) {
    *_port &= ~convertOutNumberToBit(_pin);
}

void SoftSPI_ToggleClock(void) {
    setBit(p_clock_port, clock_pin);
    SoftSPI_Delay();
    clearBit(p_clock_port, clock_pin);
    SoftSPI_Delay();
}

void SoftSPI_TriggerOutput(void) {
    if (!SoftSPI_IsInitialized()) {
        return;
    }
    setBit(p_latch_port, latch_pin);
    SoftSPI_Delay();
    clearBit(p_latch_port, latch_pin);
}
