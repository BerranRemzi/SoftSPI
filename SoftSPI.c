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

/**
 * Section: Static Variables Definitions
 */
static uint8_t dummy_cycles = MIN_DELAY_TICKS;

static volatile uint8_t * p_clock_port = 0;
static int8_t clock_pin;

static volatile uint8_t * p_select_port = 0;
static int8_t select_pin;

static volatile uint8_t * p_mosi_port = 0;
static int8_t mosi_pin;

static volatile uint8_t * p_miso_port = 0;
static int8_t miso_pin;

    /**
     * @brief Function for delay.
     * 
     * this function looping through dummy processor cycles and generating delay
     *
     * @author Berran Remzi
     * @return @c NULL is always returned.
     * @date 7.04.2019
     */
    static inline void SoftSPI_Delay(void);


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
    SoftSPI_InitDataInPin(_port, _miso_pin);
    SoftSPI_InitClockPin(_port, _clock_pin);
    SoftSPI_InitSelectPin(_port, _select_pin);
}

static inline void SoftSPI_Delay(void) {
    volatile uint8_t _counter = dummy_cycles;
    while (_counter--);
}

void SoftSPI_InitDataOutPin(volatile uint8_t * _port, int8_t _pin) {
    p_mosi_port = _port;
    mosi_pin = _pin;
}

void SoftSPI_InitDataInPin(volatile uint8_t * _port, int8_t _pin) {
    p_miso_port = _port;
    miso_pin = _pin;
}

void SoftSPI_InitClockPin(volatile uint8_t * _port, int8_t _pin) {
    p_clock_port = _port;
    clock_pin = _pin;
}

void SoftSPI_InitSelectPin(volatile uint8_t * _port, int8_t _pin) {
    p_select_port = _port;
    select_pin = _pin;
}

uint8_t SoftSPI_Write(uint8_t _value, uint8_t _bit_order) {
    uint8_t inputData = 0u;
    uint8_t bit_mask;
    
    if(_bit_order == SOFT_SPI_MSB_FIRST) {
        bit_mask = 0x80u;
    } else {
        bit_mask = 0x01u;
    }
    for (uint8_t i = 0u; i < 8u; i++) {
        if (NO_PIN < mosi_pin) {
            (_value & bit_mask) ? setBit(p_mosi_port, mosi_pin) : clearBit(p_mosi_port, mosi_pin);
            (_bit_order == SOFT_SPI_MSB_FIRST) ? (bit_mask >>= 1u) : (bit_mask <<= 1u);
        }
        setBit(p_clock_port, clock_pin);
        SoftSPI_Delay();

        if (NO_PIN < miso_pin) {
            uint8_t shift_count = (_bit_order == SOFT_SPI_MSB_FIRST) ? 7u - i : i;
            inputData |= (readBit(p_miso_port, miso_pin) << shift_count);
        }
        clearBit(p_clock_port, clock_pin);
        SoftSPI_Delay();
    }
    return inputData;
}

void setBit(volatile uint8_t * _port, uint8_t _pin) {
    *_port |= 1u << _pin;
}

void clearBit(volatile uint8_t * _port, uint8_t _pin) {
    *_port &= ~(1u << _pin);
}

bool readBit(volatile uint8_t * _port, uint8_t _pin) {
    return (*_port >> _pin) & 1u;
}

void SoftSPI_WriteChipSelect(bool _state) {
    if (NO_PIN < select_pin) {
        if(true == _state){
            setBit(p_select_port, select_pin);
        } else {
            clearBit(p_select_port, select_pin);
        }
    }
}

