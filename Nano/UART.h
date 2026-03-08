#ifndef UART_H
#define UART_H
#include <Nano.h>
#include <Base.h>

class UART : Base{
    public:
    static inline void setBaudRate(unsigned int speed){
        // uint16_t baudRate=(16000000/(16*speed))-1;
        // reference(Registers::R_UBRR0H)=static_cast<uint8_t>(baudRate>>8);
        // reference(Registers::R_UBRR0L)=static_cast<uint8_t>(baudRate);
        reference(Registers::R_UBRR0H)=103>>8;
        reference(Registers::R_UBRR0L)=103;
    }
    static inline void setReceiveInterrupt(){
        reference(Registers::R_UCSR0B)|=(1 << RXEN0) | (1 << RXCIE0);
    }
    static inline void clearReceiveInterrupt(){
        reference(Registers::R_UCSR0B)&=~(1<<RXEN0);
    }
    static inline void setTransmitInterrupt(){
        reference(Registers::R_UCSR0B)|=(1<<TXEN0);
    }
    static inline void clearTransmitInterrupt(){
        reference(Registers::R_UCSR0B)&=~(1<<TXEN0);
    }
    static inline void setDefaultSettings(){
        setBaudRate(9600);
        setReceiveInterrupt();
        setTransmitInterrupt();
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
        sei();
    }
    static inline void print(const char* string){

    }
    static inline void print(const char c){
        while (!(reference(Registers::R_UCSR0A) & (1 << UDRE0)));
        reference(Registers::R_UDR0)=c;
    }
    static inline void println(const char* string){
        for(int i=0;string[i]!='\0';++i){
            print(string[i]);
        }
        print('\n');
    }
    static inline unsigned char receive(){
        while (!(reference(Registers::R_UCSR0A) & (1 << RXC0)));
        return reference(Registers::R_UDR0);
    }
};
#endif // UART_H
