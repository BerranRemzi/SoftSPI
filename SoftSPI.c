// Copyright 2019 Berran Remzi
/**
 * @file SoftSPI.h
 * @brief this header file will contain all required
 * definitions and basic utilities functions.
 *
 * @author Berran Remzi
 *
 * @date 20.08.2019
 */
#include "SoftSPI.h"

inline uint8_t SoftSPI_IsInitialized(void) {
    return init_level == ALL_INPUTS_ARE_INITIALIZED;
}

void SoftSPI_InitDelay(uint8_t _dummy_cycles) {
    dummy_cycles = _dummy_cycles;
}

void SoftSPI_Init(
    volatile uint8_t * _port,
    int8_t _mosi_pin,
    int8_t _miso_pin,
    int8_t _clock_pin,
    int8_t _select_pin) {
    SoftSPI_InitDataOutPin(_port, _mosi_pin);
    SoftSPI_InitClockPin(_port, _clock_pin);
    SoftSPI_InitSelectPin(_port, _select_pin);

    p_mosi_port = _port;
    miso_pin = _miso_pin;
}

static inline uint8_t convertOutNumberToBit(uint8_t _pin) {
    return 1 << _pin;
}


static inline void SoftSPI_Delay(void) {
    uint8_t _counter = dummy_cycles;
    while ( _counter > 0 ) {
        _counter--;
    }
}

void SoftSPI_InitDataOutPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 0);
    }
    p_mosi_port = _port;
    mosi_pin = _pin;
}

void SoftSPI_InitClockPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 1);
    }
    p_clock_port = _port;
    clock_pin = _pin;
}

void SoftSPI_InitSelectPin(volatile uint8_t * _port, uint8_t _pin) {
    if (_port) {
        setBit(&init_level, 2);
    }
    p_select_port = _port;
    select_pin = _pin;
}

uint8_t SoftSPI_Write(uint8_t _value, uint8_t _bit_order) {
    uint8_t inputData = 0;

    /*if (!SoftSPI_IsInitialized()) {
        return 0x00;
    }*/

    for (uint8_t i = 0; i < 8; i++) {
        if ( mosi_pin >= 0 ) {
            switch (_bit_order) {
            case SOFT_SPI_MSB_FIRST:
                if ((_value >> i) & 0x01) {
                    setBit(p_mosi_port, mosi_pin);
                } else {
                    clearBit(p_mosi_port, mosi_pin);
                }
                break;
            case SOFT_SPI_LSB_FIRST:
                if ((_value << i) & 0x80) {
                    setBit(p_mosi_port, mosi_pin);
                } else {
                    clearBit(p_mosi_port, mosi_pin);
                }
                break;
            default: break;
            }
        }
        if ( miso_pin >= 0 ) {
            inputData |= readBit(p_mosi_port, miso_pin);
            if ( i < 7 ) {
                inputData = inputData << 1;
            }
        }
        SoftSPI_ToggleClock();
    }
    return inputData;
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

bool readBit(volatile uint8_t * _port, uint8_t _pin) {
    return (* _port >> _pin) & 1U;
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
    setBit(p_select_port, select_pin);
    SoftSPI_Delay();
    clearBit(p_select_port, select_pin);
}
