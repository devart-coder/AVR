#include <Nano.h>
#include <Delay.h>
#include <ExternalInterrupt.h>
#include <Bus.h>
#include <Timer0.h>
#include <Delay.h>

static int8_t counter = 0;
using namespace Nano;
void breath(uint8_t delay){
    for(uint8_t i=0; i < 255; ++i){
        SystemClock::setCounterA(i);
        delayMs(delay);
    }
    for(uint8_t i=0; i < 255; ++i){
        SystemClock::setCounterB(i);
        delayMs(delay);
    }
}
int main()
{
    PinD6::setDirection(Direction::OUTPUT);
    using Red = PinD4;
    using Green = PinD3;
    using Blue = PinD5;

    using RGB = Bus<Red, Green, Blue>;
    RGB::setDirection(1);

    using Motor = PinD6;
    PinD6::setDirection(Direction::OUTPUT);

    using Button = EID2;
    Button::setDefaultSettings();
    Button::setCallback([](){
        ++counter;
        counter%=8;
    });

    SystemClock::setDefaultSettings();
    SystemClock::setCounterB(0);
    SystemClock::setCallbackByMatchA([](){
        Motor::setLow();
        if(counter>=6)
        RGB::write(!counter);
    });
    SystemClock::setCallbackByMatchB([](){
        Motor::setHigh();
        if(counter>=6)
        RGB::write(counter);
    });
    SystemClock::start();

    while(1){

        switch(counter){
            case 0:
                SystemClock::setCounterA(1);
                break;
            case 1:
                // SystemClock::setCounterA((uint8_t)(((254*25)/100)*counter));
                // break;
            case 2:
            case 3:
            case 4:
            case 5:
                SystemClock::setCounterA((uint8_t)(((254*2)/10)*counter));
                break;
            case 6:
                breath(5);
                break;
            case 7:
                breath(10);
                break;
        }
        RGB::write(counter);
    }
    return 0;
}

