#ifndef PIN_H
#define PIN_H
#include <inttypes.h>
#include "../Nano/Atmega328p.h"
#include "Port.h"
namespace Utils{
enum class Direction:uint8_t{
    INPUT,
    OUTPUT,
    INPUT_PULL_UP
};

template<class PORT, uint8_t BIT>
class Pin
{
public:
    static constexpr uint8_t pinNumber = (1<<BIT);
    using portType = PORT;

    static void setHigh()
    {
        portType::writeMask(pinNumber);
    }
    static void setLow()
    {
        portType::clearMask(pinNumber);
    }
    static void toggle(){
        portType::writeMask(portType::read()^pinNumber);
    }
    static bool isHigh(){
        return (portType::read()&(1<<BIT)) ? true : false;
    }
    static void setDirection( Direction dir){
        switch(dir){
            case Direction::INPUT:
                portType::resetDirectionMask(pinNumber);
                break;
            case Direction::INPUT_PULL_UP:
                portType::resetDirectionMask(pinNumber);
                Pin::setHigh();
                break;
            case Direction::OUTPUT:
                portType::setDirectionMask(pinNumber);
                break;
        }
    }
};
}
#endif // PIN_H
