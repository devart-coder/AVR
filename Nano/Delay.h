#ifndef DELAY_H
#define DELAY_H
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Timer0.h>

inline void delayMs(uint16_t MS){
    _delay_ms(MS);
}
inline void delayUs(uint16_t US){
    _delay_us(US);
}

class Delay{
    public:
    static inline uint32_t millis(){

    }

};

#endif // DELAY_H
