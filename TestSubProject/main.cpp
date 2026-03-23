#include <Nano.h>
#include <Delay.h>
#include <ExternalInterrupt.h>
#include <Bus.h>
#include <Timer.h>
#include <Delay.h>

static int8_t counter = 0;
using namespace Nano;

using Red = PinD4;
using Green = PinD3;
using Blue = PinD5;
using RGB = Bus<Red, Green, Blue>;

using Button = EID2;
using MotorsD = Bus<PinD6, PinD7>;
using MotorsB = Bus<PinD8, PinD9, PinD10, PinD11, PinD12, PinD13>;
using MotorsC = Bus<PinA0, PinA1, PinA2, PinA3, PinA4, PinA5>;

void breath(uint8_t delay){
    static bool switcher = false;
    for(uint8_t i=0; i < 255; ++i){
        if(switcher)
            SystemClock::Action::setCounterB(i);
        else
            SystemClock::Action::setCounterA(i);
        delayMs(delay);
    }
    switcher=!switcher;
}
int main()
{
    RGB::setDirection(1);

    //Motors
    MotorsD::setDirection(0xff);
    MotorsB::setDirection(0xff);
    MotorsC::setDirection(0xff);

    //Button
    Button::setDefaultSettings();
    Button::setCallback([](){
        ++counter;
        counter%=8;
    });

    //Clock
    SystemClock::Interruptes::enableAChannel();
    SystemClock::Interruptes::enableBChannel();
    SystemClock::Settings::setDefaultSettings();

    SystemClock::Action::setCounterB(0);
    SystemClock::Callback::byMatchA([](){
        MotorsD::get<0>::setLow();
        MotorsD::get<1>::setLow();
        MotorsB::write(0);
        MotorsC::write(0);
        if(counter>=6)
            RGB::write(!counter);
    });
    SystemClock::Callback::byMatchB([](){
        MotorsD::get<0>::setHigh();
        MotorsD::get<1>::setHigh();
        MotorsB::write(0xff);
        MotorsC::write(0xff);
        if(counter>=6)
            RGB::write(counter);
    });
    SystemClock::Action::start();

    while(1){
        switch(counter){
            case 0:
                SystemClock::Action::setCounterA(1);
                break;
            case 6:
                breath(5);
                break;
            case 7:
                breath(10);
                break;
            default:
                SystemClock::Action::setCounterA((uint8_t)(((254*2)/10)*counter));
        }
        RGB::write(counter);
    }
    return 0;
}
