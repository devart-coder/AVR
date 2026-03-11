#include <Nano.h>
#include <Delay.h>
#include <Timer0.h>
#include <UART.h>
using namespace Nano;
int main()
{
    UART::setDefaultSettings();
    UART::setReceiveCallback([](){
        uint8_t r = UART::receive();
        if(r == '1' ){
            PinD4::toggle();
            UART::print("Result: ");
            UART::println(123);
        }
        if(r == '2' )
            PinD5::toggle();
        if(r == '3' )
            PinD6::toggle();
    });
    PinD4::setMode(PinD4::Direction::OUTPUT);
    PinD5::setMode(PinD5::Direction::OUTPUT);
    PinD6::setMode(PinD6::Direction::OUTPUT);
    for(;;){
    }
    return 0;
}

