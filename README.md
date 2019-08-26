# SoftSPI
This is a simple library to simplify bit-banging SPI on any MCU.
It accepts port address as pointer and pin number for every output.

---

## Example code for PIC12F1840 and 74HC595 with XC8 compiler

```c

#include <xc.h>
#include <stdint.h>
#include "configuration.h"
#include "SoftSPI.h"

#define MOSI_PIN 3
#define MISO_PIN 0
#define CLOCK_PIN 1
#define SELECT_PIN 2

void init(void){
   LATA = 0x00;
   TRISA = 0x00;
}

void main(void)
{
    uint8_t counter = 0;
    init();
    SoftSPI_Init(&PORTA, MOSI_PIN, MISO_PIN, CLOCK_PIN, SELECT_PIN);
    SoftSPI_InitDelay(10); // by default this is 1 cycle
    for(;;){
        SoftSPI_Write(counter++, SOFT_SPI_LSB_FIRST);
        SoftSPI_TriggerOutput();
        __delay_ms(500);
    }
}

```

## Example code for PIC12F1840 and MCP3201 with XC8 compiler

```c

#include <xc.h>
#include <stdint.h>
#include "configuration.h"
#include "SoftSPI.h"

#define MOSI_PIN 3
#define MISO_PIN 0
#define CLOCK_PIN 1
#define SELECT_PIN 2

union {
    uint8_t dataByte[2];
    uint16_t result;
} adc;

void main(void)
{
    init();
    SoftSPI_Init(&PORTA, MOSI_PIN, MISO_PIN, CLOCK_PIN, SELECT_PIN);
    for(;;) {
        clearBit(&PORTA, SELECT_PIN);
        adc.dataByte[1] = SoftSPI_Write(0, SOFT_SPI_LSB_FIRST);
        adc.dataByte[0] = SoftSPI_Write(0, SOFT_SPI_LSB_FIRST);
        setBit(&PORTA, SELECT_PIN);

        adc.result >>= 1; // adjust composite integer for 12 valid bits
        adc.result &= 0x0FFF; // mask out upper nibble of integer
        
        printf("%u\n\r", adc.result);
    }
}

```

## Initializing ports
Use these three functions:

```c
   SoftSPI_InitDataPin(&PORTA, 0);
   SoftSPI_InitClockPin(&PORTA, 1);
   SoftSPI_InitLatchPin(&PORTA, 2);
```

or:

```c
//SoftSPI_Init(&PORTA, MOSI_PIN, MISO_PIN, CLOCK_PIN, SELECT_PIN);
SoftSPI_Init(&PORTA, 0, 1, 2, 3);
```

or initialize only MISO or MOSI with pin number -1:

```c
//SoftSPI_Init(&PORTA, MOSI_PIN, MISO_PIN, CLOCK_PIN, SELECT_PIN);
SoftSPI_Init(&PORTA, -1, 1, 2, 3);
```

## Changing number of dummy processor cycles
If the value isn't initialized, default is 1 processor cycle

```c
SoftSPI_InitDelay(10); // min = 0, max = 255;
```

## Authors

* **Berran Remzi** - *Initial work* - [BerranRemzi](https://github.com/BerranRemzi)

See also the list of [contributors](https://github.com/BerranRemzi/SoftSPI/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

