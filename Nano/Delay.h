#ifndef DELAY_H
#define DELAY_H
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Timer0.h>

inline void delayMs(uint16_t MS){
    while(MS--){
        _delay_ms(1);
    }
}
inline void delayUs(uint16_t US){
    while(US--){
        _delay_ms(1);
    }
}

class Delay{
    public:
    static inline uint32_t millis(){

    }

};

#endif // DELAY_H
