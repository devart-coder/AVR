#include <Nano.h>
#include <ExternalInterrupt.h>
#include <Delay.h>
#include <Bus.h>
using namespace Nano;
volatile uint8_t counter = 0;
using B = Bus< PinD2, PinD4, PinD6 >;
int main()
{
    PinD7::setMode(PinD7::Direction::OUTPUT);
    PinD7::setHigh();
    // B::setBusDirectionMask(0xff);
    // B::write(2);
    for(int i=0; ;++i,i%=8){
        B::write(i);
        delayMs(500);
    }
    return 0;
}

