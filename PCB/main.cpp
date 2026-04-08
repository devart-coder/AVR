#define F_CPU 16000000UL
#include <Nano.h>
#include <UART.h>
#include <GCListener.h>
#include <Utils.h>
using namespace Nano;
int main()
{
    while(1){
        uart.out.println(Utils::Conversions::toDigital("1234"));
        uart.out.println(Utils::Conversions::toDigital("8765"));
        delayMs(1000);
    }
    return 0;
}
