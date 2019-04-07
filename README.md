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
    SoftSPI_InitDelay(10); // by default this is 1 cycle
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

istead of

```c
SoftSPI_Init(&PORTA, 0, 1, 2);
```

## Changing number of dummy processor dummy cycles
If the value isn't initialized, it starts with 1 processor cycle

```c
SoftSPI_InitDelay(10); // min = 1, max = 255;
```
