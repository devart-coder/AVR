#include <Nano.h>
#include <ExternalInterrupt.h>
using namespace Nano;
int main()
{
    PinD4::setMode(PinD4::Direction::OUTPUT);
    PinD5::setMode(PinD5::Direction::OUTPUT);
    PinD6::setMode(PinD6::Direction::OUTPUT);
    PinD2::setMode(PinD2::Direction::INPUT);
    PinD2::setHigh();
    EID2::setDefaultSettings();
    EID2::setCallback([](){
        PinD4::toggle();
    });
    for(;;){
    }
    return 0;
}

