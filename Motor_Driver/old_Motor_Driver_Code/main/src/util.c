#include "../include/util.h"
#include "../include/config.h"
#include PICINCLUDE

#include <libpic30.h>

inline void delay_ms(unsigned int t) {
    uint16 i;
    for (i = 0; i < t; i++) {
        __delay_ms(1);
    }
}

inline void delay_us(unsigned int t) {
    uint16 i;
    for (i = 0; i < t; i++) {
        __delay_us(1);
    }
}
