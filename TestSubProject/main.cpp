#include <Nano.h>
#include <Delay.h>
#include <Timer0.h>
#include <UART.h>
using namespace Nano;
static volatile uint8_t counter=0b11110000;
ISR(USART_RX_vect) {
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
}
int main()
{
    UART::setDefaultSettings();
    PinD4::setMode(PinD4::Direction::OUTPUT);
    PinD5::setMode(PinD5::Direction::OUTPUT);
    PinD6::setMode(PinD6::Direction::OUTPUT);
    for(;;){
    }
    return 0;
}

