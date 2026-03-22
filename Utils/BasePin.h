#ifndef BASEPIN_H
#define BASEPIN_H
#include <inttypes.h>
// #include <Atmega328p.h>
// #include <Utils.h>
// using Atmega328p::Registers;
// using namespace Utils;

enum class Direction:uint8_t{
        INPUT,
        OUTPUT,
        INPUT_PULL_UP
    };


template<class PORT, uint8_t pinNumber>
class BasePin
{
    public:
        constexpr BasePin() {}
        static void setDirection( Direction dir){
            switch(dir){
                case Direction::INPUT:
                    PORT::resetDirectionMask(pinNumber);
                    break;
                case Direction::INPUT_PULL_UP:
                    PORT::resetDirectionMask(pinNumber);
                    // setHigh();
                    break;
                case Direction::OUTPUT:
                    PORT::setDirectionMask(pinNumber);
                    break;
            }
        }
};

#endif // BASEPIN_H
