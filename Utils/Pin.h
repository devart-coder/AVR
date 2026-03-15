#ifndef PIN_H
#define PIN_H
#include <inttypes.h>
#include "../Nano/Atmega328p.h"
#include "Port.h"
template<class PORT, uint8_t BIT>
class Pin
{
public:
    static constexpr uint8_t pinNumber = (1<<BIT);
    using portType = PORT;
    enum class Direction:uint8_t{
        INPUT,
        OUTPUT,
        INPUT_PULL_UP
    };
    static void setHigh()
    {
        portType::writeMask(1<<BIT);
    }
    static void setLow()
    {
        portType::clearByMask(1<<BIT);
    }
    static void toggle(){
        portType::write(portType::read()^(1<<BIT));
    }
    static bool isHigh(){
        return (portType::read()&(1<<BIT)) ? true : false;
    }
    static void setMode( Direction dir){
        switch(dir){
            case Direction::INPUT:
                portType::resetDirectionMask(1<<BIT);
                break;
            case Direction::INPUT_PULL_UP:
                portType::resetDirectionMask(1<<BIT);
                Pin::setHigh();
                break;
            case Direction::OUTPUT:
                portType::setDirectionMask(1<<BIT);
                break;
        }
    }
};

#endif // PIN_H
