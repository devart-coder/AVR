#ifndef PORT_H
#define PORT_H
#include <Atmega328p.h>
#include <inttypes.h>
#include <Base.h>
using Atmega328p::Registers;

template<Registers PORT>
struct Port : private Base{
        static constexpr uint16_t port = PORT;
        static constexpr uint16_t ddr = static_cast<uint16_t>(PORT)-1;
        static constexpr uint16_t pins = static_cast<uint16_t>(PORT)-2;

        static inline void setMode(uint8_t byte){
            reference(ddr)=byte;
        }
        static inline void setModeMask(uint8_t byte){
            reference(ddr)|=byte;
        }
        static inline void resetModeMask(uint8_t byte){
            reference(ddr)&=~byte;
        }
        static inline void write(uint8_t byte){
            reference(port)=byte;
        }
        static inline uint8_t read(){
            return reference(pins);
        }
        static inline void writeMask(uint8_t byte){
            reference(port)|=byte;
        }
        static inline void clearMask(uint8_t byte){
            reference(port)&=~byte;
        }
};
#endif // PORT_H
