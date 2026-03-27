#include <Nano.h>
#include <Delay.h>
// #include <Timer.h>
#include <SoftPWM.h>
using namespace Nano;
int main()
{
    using SPWM = Soft<PinD6,PinD9>;
    SPWM::action.start();
    while(1){
        for(uint8_t i=255; i!=0; --i){
            SPWM::action.setDirtyByte(i);
            delayMs(3);
        }
        for(uint8_t i=0; i!=255; ++i){
            SPWM::action.setDirtyByte(i);
            delayMs(3);
        }
    }
    return 0;
}
