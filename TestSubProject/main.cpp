#include <Nano.h>
#include <Timer.h>
#include <Delay.h>

using Nano::PinD13;
int main()
{
    Timer0::Setting::setDefaultSettings();
    Timer0::Interrupte::enableAChannel();
    Timer0::Interrupte::enableBChannel();
    Timer0::Callback::byMatchA([](){
        PinD13::setHigh();
    });
    Timer0::Callback::byMatchB([](){
        PinD13::setLow();
    });

    PinD13::setMode(PinMode::OUTPUT);
    Timer0::Action::start();
    while(1){
        for(uint8_t i =0;i!=255; ++i){
            Timer0::Action::setCounterA(i);
            delayMs(1);
        }
        for(uint8_t i =0;i!=255; ++i){
            Timer0::Action::setCounterB(i);
            delayMs(1);
        }
    }
    return 0;
}
