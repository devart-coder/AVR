#include <Nano.h>
#include <Delay.h>
#include <PWM.h>
using namespace Nano;
int main()
{
    PWMD6::setDefaultSettings();
    while(1){
        for(uint8_t i =0;i!=255; ++i){
            PWMD6::setDirtyPercent(i);
            delayMs(3);
        }
        for(uint8_t i = 255;i!=0; --i){
            PWMD6::setDirtyPercent(i);
            delayMs(3);
        }
    }
    return 0;
}
