#ifndef UART_H
#define UART_H
#include <Nano.h>
#include <Base.h>
#include <Utils.h>
enum class BaudRate:unsigned long{
    _300=300,
    _1200=1200,
    _2400=2400,
    _4800=4800,
    _9600=9600,
    _19200=19200,
    _38400=38400,
    _57600=57600,
    _115200=115200
};
class UART : Base{
    private:
        using HandleType = void (*)();
        static inline HandleType transmissionCallBack = nullptr;
        static inline HandleType receiveCallBack = nullptr;
    public:
    enum class PackageBits{
        _5,
        _6,
        _7,
        _8,
        _9,
    };
    enum class ParityMode{
        Disabled,
        Even,
        Odd
    };
    static inline void setPackageBits(PackageBits pb){
        switch(pb){
            case PackageBits::_5:
                reference(Registers::R_UCSR0C)&=~((1<<UCSZ01) | (1<<UCSZ00));
                break;
            case PackageBits::_6:
                reference(Registers::R_UCSR0C)|=(1<<UCSZ00);
                break;
            case PackageBits::_7:
                reference(Registers::R_UCSR0C)|=(1<<UCSZ01);
                break;
            case PackageBits::_9:
                reference(Registers::R_UCSR0B)|=(1<<UCSZ02);
            case PackageBits::_8:
                reference(Registers::R_UCSR0C)|=(1<<UCSZ00)|(1<<UCSZ01);
        };
    }
    static inline void setParityMode(ParityMode mode){
        switch(mode){
            case ParityMode::Disabled:
                reference(Registers::R_UCSR0C)&=~((1<<UPM00)|(1<<UPM01));
                break;
            case ParityMode::Odd:
                reference(Registers::R_UCSR0C)|=(1<<UPM00);
            case ParityMode::Even:
                reference(Registers::R_UCSR0C)|=(1<<UPM01);
                break;
        }
    }
    static inline void setOneStopBit(){
        reference(Registers::R_UCSR0C) &= ~(1<<USBS0);
    }
    static inline void setTwoStopBits(){
        reference(Registers::R_UCSR0C) |= (1<<USBS0);
    }
    static inline void setBaudRate(BaudRate boudRate){
        unsigned int baudRate=(F_CPU/(16UL*static_cast<unsigned long>(boudRate)))-1;
        reference(Registers::R_UBRR0H)=baudRate>>8;
        reference(Registers::R_UBRR0L)=baudRate;
    }
    static inline void enableReceiveInterrupt(bool flag){
        flag == true ?
        reference(Registers::R_UCSR0B)|=(1 << RXEN0)|(1 << RXCIE0) :
        reference(Registers::R_UCSR0B)&=~(1<<RXEN0);
    }
    static inline void enableTransmissionInterrupt( bool flag){
        flag == true ?
        reference(Registers::R_UCSR0B)|=(1<<TXEN0) :
        reference(Registers::R_UCSR0B)&=~(1<<TXEN0);
    }
    static inline void setDefaultSettings(){
        cli();

        setBaudRate(BaudRate::_9600);
        enableTransmissionInterrupt(true);
        enableReceiveInterrupt(true);

        setPackageBits(PackageBits::_8);
        setParityMode(ParityMode::Disabled);
        setOneStopBit();

        sei();
    }
    static inline void setTransmissionCallback(HandleType handle){
        transmissionCallBack = handle;
    }
    static inline void setReceiveCallback(HandleType handle){
        receiveCallBack = handle;
    }
    static void receiveHandle(){
        receiveCallBack();
    }
    static void transmissionHandle(){
        transmissionCallBack();
    }
    static inline void print(char* string){
        for(int i=0;string[i]!='\0';++i)
            print(string[i]);
    }
    static inline void print(char c){
        while (!(reference(Registers::R_UCSR0A) & (1 << UDRE0)));
        reference(Registers::R_UDR0)=c;
    }
    static inline void print(unsigned int number){
            char result[Utils::Conversions::digits(number)+1];
            Utils::Conversions::toString(number,result);
            print(result);
    }

    static inline void println(char* string=""){
        print(string);
        print('\n');
    }
    static inline void println(unsigned int number){
        print(number);
        print('\n');
    }
    static inline void println(char c){
        print(c);
        print('\n');
    }
    static inline unsigned char receive(){
        while (!(reference(Registers::R_UCSR0A) & (1 << RXC0)));
        return reference(Registers::R_UDR0);
    }
};
ISR(USART_RX_vect) {
    UART::receiveHandle();
}
ISR(USART_TX_vect) {
    UART::transmissionHandle();
}
#endif // UART_H
