#include <Nano.h>
// #include <ExternalInterrupt.h>
#include <Delay.h>
#include <Bus.h>
#include <Timer0.h>
// #include <PWD.h>
using namespace Nano;
using RGB = Bus< PinD2, PinD4, PinD6, PinD5>;
using LED = SystemClock;
static uint32_t counter=0;
int main()
{
    RGB::setDirection(0b0001);
    LED::setDefaultSettings();
    LED::setCallback([](){
        ++counter;
        counter%=800*2;
    });
    LED::start();
    for(int i=0; ; ++i, i%=8){
        if(counter==1000){
            LED::stop();
            RGB::get<3>::toggle();
            delayMs(1000);
            counter=200;
            LED::start();
        }
        RGB::write(counter/200);
    }
    return 0;
}

