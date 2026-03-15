#ifndef NANO_H
#define NANO_H
#include "Atmega328p.h"
#include "../Utils/Pin.h"
#include "../Utils/Port.h"
namespace Nano{
    using Utils::Pin;
    using Utils::Direction;
    using Atmega328p::Registers;

    using PortD = Port<Registers::R_PORTD>;
    using PortC = Port<Registers::R_PORTC>;
    using PortB = Port<Registers::R_PORTB>;

    using PinD0  = Pin<PortD, 0>;
    using PinD1  = Pin<PortD, 1>;
    using PinD2  = Pin<PortD, 2>;
    using PinD3  = Pin<PortD, 3>;
    using PinD4  = Pin<PortD, 4>;
    using PinD5  = Pin<PortD, 5>;
    using PinD6  = Pin<PortD, 6>;
    using PinD7  = Pin<PortD, 7>;

    using PinD8  = Pin<PortB, 0>;
    using PinD9  = Pin<PortB, 1>;
    using PinD10 = Pin<PortB, 2>;
    using PinD11 = Pin<PortB, 3>;
    using PinD12 = Pin<PortB, 4>;
    using PinD13 = Pin<PortB, 5>;

    using PinA0 = Pin<PortC, 0>;
    using PinA1 = Pin<PortC, 1>;
    using PinA2 = Pin<PortC, 2>;
    using PinA3 = Pin<PortC, 3>;
    using PinA4 = Pin<PortC, 4>;
}
#endif // NANO_H
