#ifndef DELAY_H
#define DELAY_H
#include <util/delay.h>
#include <avr/interrupt.h>

inline void delayMs(uint16_t MS){
    _delay_ms(MS);
}
inline void delayUs(uint16_t US){
    _delay_us(US);
}
#endif // DELAY_H
