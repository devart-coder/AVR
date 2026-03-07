#ifndef PORT_H
#define PORT_H
#include <Atmega328p.h>
#include <inttypes.h>
#include <Base.h>
using Atmega328p::Registers;

template<Registers PORT>
class Port : private Base{
        static constexpr uint16_t port = PORT;
        static constexpr uint16_t ddr = static_cast<uint16_t>(PORT)-1;
        static constexpr uint16_t pin = static_cast<uint16_t>(PORT)-2;
    public:
        static inline void setMode(uint8_t byte){
            reference(ddr)=byte;
        }
        static inline void setModeByMask(uint8_t byte){
            reference(ddr)|=byte;
        }
        static inline void clearModeByMask(uint8_t byte){
            reference(ddr)&=~byte;
        }
        static inline void write(uint8_t byte){
            reference(port)=byte;
        }
        static inline uint8_t read(){
            return reference(port);
        }
        static inline void writeMask(uint8_t byte){
            reference(port)|=byte;
        }
        static inline void clearByMask(uint8_t byte){
            reference(port)&=~byte;
        }
};
#endif // PORT_H
