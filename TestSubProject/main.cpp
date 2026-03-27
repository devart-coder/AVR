#include <Nano.h>
#include <Delay.h>
#include <UART.h>
// #include <Timer.h>
// #include <SoftPWM.h>
using namespace Nano;
int main()
{
    UART::Setting::defaultSettings();
    while(1){
        System.out.println("Hello");
        delayMs(1000);
    }
    return 0;
}
