#include <Nano.h>
#include <Delay.h>
#include <Timer0.h>
// #include <PWD.h>
using namespace Nano;
static volatile uint8_t counter=0b11110000;
int main()
{
    // PinD5::setMode(PinD5::Direction::OUTPUT);
    PinD5::portType::setModeByMask(counter);
    Clock::setDefaultSettings();
    Clock::setCallbackByOverFlow([](){
        counter=~(counter);
        PinD5::portType::write(counter);
    });
    for(;;){
    }
    return 0;
}

