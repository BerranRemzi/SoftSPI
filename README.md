# SoftSPI
Software SPI with bit-bang control of outputs

---

## Example (Optional)

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

---
