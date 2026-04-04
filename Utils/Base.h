#ifndef BASE_H
#define BASE_H
#include <inttypes.h>
    class Base
    {
        protected:
        static volatile uint8_t& reference(uint16_t addr){
            return *reinterpret_cast<volatile uint8_t*>(addr);
        }
    };
#endif // BASE_H
