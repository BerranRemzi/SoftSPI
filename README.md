# SoftSPI
This is a simple library to simplify bit-banging SPI on any MCU.
It accepts port address as pointer and pin number for every output.

---

## Example code for PIC12F1840 with XC8 compiler

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

## Changing number of dummy processor cycles
If the value isn't initialized, default is 1 processor cycle

```c
SoftSPI_InitDelay(10); // min = 1, max = 255;
```

## Authors

* **Berran Remzi** - *Initial work* - [BerranRemzi](https://github.com/BerranRemzi)

See also the list of [contributors](https://github.com/BerranRemzi/SoftSPI/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

