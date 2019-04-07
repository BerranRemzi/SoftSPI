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

#ifndef SOFTSPI_H_
#define SOFTSPI_H_

#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

#define MIN_DELAY_TICKS 0x01
#define ALL_INPUTS_ARE_INITIALIZED 0x07

/** 
 * An enum.
 * The bit positions in a binary number
 */
typedef enum BitNumberingEnum {
    SOFT_SPI_LSB_FIRST, /**< Least significant bit. */
    SOFT_SPI_MSB_FIRST  /**< Most significant bit. */
};

/**
 * Section: Global Variables Definitions
*/
static uint8_t init_level = 0;
static uint8_t dummy_cycles = MIN_DELAY_TICKS;

static volatile uint8_t * p_clock_port = 0;
static uint8_t clock_pin;

static volatile uint8_t * p_latch_port = 0;
static uint8_t latch_pin;

static volatile uint8_t * p_data_port = 0;
static uint8_t data_pin;

/**
 * @brief Function for checking initialization status of API.
 *
 * a normal member that returning an uint8_t value.
 * @author Berran Remzi
 * @return Function returns API initialization status
 * @date 7.04.2019
 */
inline uint8_t SoftSPI_IsInitialized();

/**
 * @brief Function for initialization dummy cycles for delay.
 *
 * 
 * a normal member taking one arguments.
 * @author Berran Remzi
 * @param _dummy_cycles Value of dummy cycles
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_InitDelay(uint8_t _dummy_cycles);

/**
 * @brief Function for initialization a <b>Software SPI API</b>.
 *
 * a normal member taking four arguments.
 * @author Berran Remzi
 * @param *_port Port address that SPI line is connected.
 * @param _data_pin Pin number of DATA line.
 * @param _clock_pin pin number of CLOCK line.
 * @param _latch_pin Pin number of LATCH line.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_Init(
    volatile uint8_t * _port,
    uint8_t _data_pin,
    uint8_t _clock_pin,
    uint8_t _latch_pin);

/**
 * @brief Function for setting single a bit from specified port.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param *_port Port address.
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void setBit(volatile uint8_t * _port, uint8_t _pin);

/**
 * @brief Function for clearing single a bit from specified port.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param *_port Port address.
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void clearBit(volatile uint8_t * _port, uint8_t _pin);

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

/**
 * @brief Function for clearing the output.
 *
 * This function send 0x00 to output.
 * @author Berran Remzi
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_Clear(void);

/**
 * @brief Function for writing one byte to the output.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param _value Value that will be wrote on SPI output.
 * @param _bit_order Bit ordering on binary number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_Write(uint8_t _value, uint8_t _bit_order);

/**
 * @brief Function for toggling the CLOCK pin
 *
 * @author Berran Remzi
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_ToggleClock();

/**
 * @brief Function for toggling the LATCH pin
 *
 * @author Berran Remzi
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_TriggerOutput();

/**
 * @brief Function for converting pin number to port bit.
 *
 * a normal member taking one arguments.
 * @author Berran Remzi
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
static inline uint8_t convertOutNumberToBit(uint8_t _pin);

/**
 * @brief Function for initializing DATA output.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param *_port Port address.
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_InitDataPin(volatile uint8_t * _port, uint8_t _pin);

/**
 * @brief Function for initializing DATA output.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param *_port Port address.
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_InitLatchPin(volatile uint8_t * _port, uint8_t _pin);

/**
 * @brief Function for initializing LATCH output.
 *
 * a normal member taking two arguments.
 * @author Berran Remzi
 * @param *_port Port address.
 * @param _pin Pin number.
 * @return @c NULL is always returned.
 * @date 7.04.2019
 */
void SoftSPI_InitClockPin(volatile uint8_t * _port, uint8_t _pin);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // SOFTSPI_H_

/**
End of File
 */

