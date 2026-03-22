#ifndef PIN_H
#define PIN_H
#include <inttypes.h>
#include "../Nano/Atmega328p.h"
#include "Port.h"
enum class PinMode{
    INPUT,
    OUTPUT,
    INPUT_PULL_UP
};

namespace Utils{

    template<class PORT, uint8_t BIT>
    struct Pin
    {
        static constexpr uint8_t pinNumber = (1<<BIT);
        using portType = PORT;

        static inline void setHigh()
        {
            portType::writeMask(pinNumber);
        }
        static inline void setLow()
        {
            portType::clearMask(pinNumber);
        }
        static inline void toggle(){
            portType::write (portType::read()^pinNumber);
        }
        static inline bool isHigh(){
            return (portType::read()&(1<<BIT)) ? true : false;
        }
        static inline bool isLow(){
            return !isHigh();
        }
        static inline void setMode( PinMode pinMode){
            switch(pinMode){
                case PinMode::INPUT:
                    portType::resetModeMask(pinNumber);
                    break;
                case PinMode::INPUT_PULL_UP:
                    portType::resetModeMask(pinNumber);
                    setHigh();
                    break;
                case PinMode::OUTPUT:
                    portType::setModeMask(pinNumber);
                    break;
            }
        }
    };
}
#endif // PIN_H
