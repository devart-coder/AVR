#include <Nano.h>
#define F_CPU 16000000
#include <Delay.h>
#include <PWD.h>
using namespace Nano;
using RED = PinD3;
using GREEN = PinD4;
using BLUE = PinD5;
void f(char c){
    if(c=='A'){

        }else{

        }
}
int main()
{
    PWDD5::setDefaultSettings();
    PWDD6::setDefaultSettings();
    for(uint8_t i=0;;i+=10){
        PWDD6::setDirtyPercent(i);
        delayMs(25);
        if(i==100){
            for(uint8_t j=0;j!=100;j+=10){
                PWDD6::setDirtyPercent(100-j);
                delayMs(25);
            }
            i=0;
        }
    }
    return 0;
}
