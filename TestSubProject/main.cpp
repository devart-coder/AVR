#include <Nano.h>
#include <ExternalInterrupt.h>
#include <Delay.h>
#include <Bus.h>
using namespace Nano;
volatile uint8_t counter = 0;
using B = Bus< PinD4, PinD5, PinD6 >;
int main()
{
    // PinD4::setMode(PinD4::Direction::OUTPUT);
    // PinD5::setMode(PinD5::Direction::OUTPUT);
    // PinD6::setMode(PinD6::Direction::OUTPUT);
    // EID2::setDefaultSettings();

    // EID2::setCallback([](){
    //     ++counter;
    //     counter%=3;
    //     delayMs(200);
    //     if(counter==0)
    //         PinD4::toggle();
    //     if(counter==1)
    //         PinD5::toggle();
    //     if(counter==2)
    //         PinD6::toggle();
    // });

    for(;;){
    }
    return 0;
}

