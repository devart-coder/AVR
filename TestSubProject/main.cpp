#include <Nano.h>
#include <ExternalInterrupt.h>
#include <Delay.h>
#include <Bus.h>
using namespace Nano;
volatile uint8_t counter = 0;
using B = Bus< PinD2, PinD4, PinD6 >;
int main()
{
    PinD2::setMode(PinD2::Direction::OUTPUT);
    PinD4::setMode(PinD4::Direction::OUTPUT);
    PinD6::setMode(PinD6::Direction::OUTPUT);
    // B::setBusModeMask(0xff);
    B::write(9);
    for(;;){
    }
    return 0;
}

