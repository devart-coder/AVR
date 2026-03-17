#include <Nano.h>
#include <ExternalInterrupt.h>
// #include <Delay.h>
// #include <Bus.h>
// #include <Timer0.h>
#include <UART.h>

static unsigned int counter = 0;
using namespace Nano;
int main()
{
    PinD13::setDirection(Direction::OUTPUT);
    EID2::setDefaultSettings();
    EID2::setCallback([](){
        counter++;
        counter%=8;
        PinD13::toggle();
    });
    while(1){

    };
    return 0;
}

