# SoftSPI
This is a simple library to simplify bit-banging SPI on any MCU.
It accepts port address as pointer and pin number for every output.

---

## Example

```c

#include <xc.h>
#include <stdint.h>
#include "configuration.h"
#include "SoftSPI.h"

void init(void){
   LATA = 0x00;
   TRISA = 0x00;
}

void main(void)
{
    uint8_t counter = 0;
    init();
    SoftSPI_Init(&PORTA, 0, 1, 2);
    for(;;){
        SoftSPI_Write(counter++, SOFT_SPI_LSB_FIRST);
        SoftSPI_TriggerOutput();
        __delay_ms(500);
    }
}

```

## Initializing ports one by one
Use these three functions:

```c
   SoftSPI_InitDataPin(&PORTA, 0);
   SoftSPI_InitClockPin(&PORTA, 1);
   SoftSPI_InitLatchPin(&PORTA, 2);
```

istead of:

```c
SoftSPI_Init(&PORTA, 0, 1, 2);
```
