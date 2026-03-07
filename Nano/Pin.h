#ifndef PIN_H
#define PIN_H
#include <inttypes.h>
#include "Atmega328p.h"
#include "Port.h"
template<class PORT, uint8_t BIT>
class Pin
{
public:
    static constexpr volatile uint8_t pinNumber = BIT;
    using portType = PORT;
    enum class Direction:uint8_t{
        INPUT,
        OUTPUT
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
        //TODO::Remake
        return true;
    }
    static void setMode( Direction dir){
        dir == Direction::OUTPUT ? portType::setModeByMask(1<<BIT) : portType::clearModeByMask(1<<BIT);
    }
};

#endif // PIN_H
