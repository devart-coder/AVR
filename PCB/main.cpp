#include <CNC.h>
#include <Delay.h>
using namespace CNC;
#define d 1
#define times 500
void f (){
    XStep::setHigh();
    YStep::setHigh();
    ZStep::setHigh();
    delayMs(d);

    XStep::setLow();
    YStep::setLow();
    ZStep::setLow();
    delayMs(d);
}
int main()
{
    XDir::setMode(PinMode::OUTPUT);
    YDir::setMode(PinMode::OUTPUT);
    ZDir::setMode(PinMode::OUTPUT);

    XStep::setMode(PinMode::OUTPUT);
    YStep::setMode(PinMode::OUTPUT);
    ZStep::setMode(PinMode::OUTPUT);

    while(1){
        XDir::setHigh();
        YDir::setHigh();
        ZDir::setHigh();
        for(uint16_t i = 0;i!=times;++i){
            f();
        }
        delayMs(100);
        XDir::setLow();
        YDir::setLow();
        ZDir::setLow();
        for(uint16_t i = 0;i!=times;++i){
            f();
        }
    }
    return 0;
}
