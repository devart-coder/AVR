#include <Nano.h>
#include <Delay.h>
#include <Timer.h>
using namespace Nano;
int main()
{
    //template<class... PINS>
    //usings SoftPWM = SoftPWM<BUS<PINS>>
    //SoftPWM::Settings::setMode(NORMAL,INVERSION);
    //SoftPWM::Action::setDirtyPercent(uint8_t );
    //SoftPWM::Action::setDirtyByte(uint8_t );

    PinD6::setMode(PinMode::OUTPUT);
    // Timer0::Action::setCounterA(1);
    // Timer0::Action::setCounterB(0);
    Timer0::Setting::setDefaultSettings();
    Timer0::Callback::byMatchA([](){
        PinD6::setLow();
    });
    Timer0::Callback::byMatchB([](){
        PinD6::setHigh();
    });
    Timer0::Action::start();
    while(1){
        for(uint8_t i=0; i!=255; ++i){
            Timer0::Action::setCounterA(i);
            delayMs(3);
        }
        for(uint8_t i=0; i!=255; ++i){
            Timer0::Action::setCounterB(i);
            delayMs(3);
        }
    }
    return 0;
}
