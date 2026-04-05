#ifndef UART_H
#define UART_H
#include <Nano.h>
#include <Base.h>
#include <Utils.h>
#include <avr/interrupt.h>
#include <Buffer.h>
template <class T , T CAP>
class Buffer;
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
using Utils::Templates::enable_if_t;
using Utils::Templates::is_numeric_v;
using Utils::Templates::is_same_v;
using namespace Atmega328p::Bits;
template<uint16_t CAP>
class UART : Base{
    static constexpr inline uint16_t _capacity = CAP;
    private:
    struct SettingInterface{
        static inline void enableDoubleSpeed(){
            reference(Registers::R_UCSR0A)|= (1 << U2X0);
        }
        static inline void disableDoubleSpeed(){
            reference(Registers::R_UCSR0A)&= ~(1 << U2X0);
        }
        static inline void setPackageBits(PackageBits pb){
            switch(pb){
                case PackageBits::_5:
                    reference(Registers::R_UCSR0C)&=~((1<<UCSZ01)|(1<<UCSZ00));
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
                    reference(Registers::R_UCSR0C)|=(1<<UPM00)|(1<<UPM01);
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
        static inline void setBaudRate(BaudRate baudRate){
            uint32_t speed=0;
            switch (baudRate) {
                case BaudRate::_115200:
                    speed=(F_CPU/(8UL*static_cast<unsigned long>(baudRate)))-1;
                    enableDoubleSpeed();
                    break;
                default:
                    speed=(F_CPU/(16UL*static_cast<unsigned long>(baudRate)))-1;
                    disableDoubleSpeed();
                    break;
            }
            reference(Registers::R_UBRR0H)=speed>>8;
            reference(Registers::R_UBRR0L)=speed;
        }
        static inline void defaultSettings(){
            cli();
            Setting::setBaudRate(BaudRate::_9600);
            Setting::setPackageBits(PackageBits::_8);
            Setting::setParityMode(ParityMode::Disabled);
            Setting::setOneStopBit();

            Interrupt::enableTransmissionInterrupt(true);
            Interrupt::enableReceiveInterrupt(true);
            sei();
        }
    };
    struct OutStreamInterface{
        static inline void print(const char* string){
            for(uint32_t i=0;string[i]!='\0';++i)
                print(string[i]);
        }
        static inline void print(bool value){
            print(value==true? "true" : "false");
        }
        static inline void print(char* string, uint32_t size){
            for(uint32_t i=0; i<=size; ++i)
                print(string[i]);
        }
        template<class T, T C>
        static inline void print(const Buffer<T,C>& buffer){
            for(auto i = buffer.begin(); i!=buffer.end(); ++i)
                print(buffer.at(i));
        }
        static inline void print(char* string, uint32_t ib, uint32_t ie){
            for(uint32_t i=ib; i!=ie; ++i, ib%= (ie-ib>0 ? ie-ib : ib-ie))
                print(string[i]);
        }
        static inline void print(char c){
            while (!(reference(Registers::R_UCSR0A) & (1 << UDRE0)));
            reference(Registers::R_UDR0)=c;
        }
        template<class T , class U = enable_if_t<(is_numeric_v<T>)>>
        static inline void print(T number){
            if(number == 0)
                print('0');
            char result[Utils::Conversions::digits(number)+1];
            Utils::Conversions::toString(number,result);
            print(result);
        }
        template< class T, class U = enable_if_t<(is_numeric_v<T>||is_same_v<T,const char*>||is_same_v<T,char>)> >
        static inline void println(T c){
            print(c);
            print('\n');
        }
        template<class T>
        static inline void println(const Buffer<T,CAP>& c){
            print(c);
            print('\n');
        }
        template<class T>
        static inline void println(bool c){
            print(c);
            print('\n');
        }
        static inline void println(char* c, uint32_t size){
            print(c, size);
            print('\n');
        }
    };
    class InStreamInterface{
        class BufferInterface{
            static inline char _buffer[_capacity]={' '};
            static inline uint16_t begin = 0;
            static inline uint16_t end = 0;
            // static inline bool endOfStringFlag = false;
        public:
            static inline char* get(){
                return _buffer;
            }
            static inline void write(char c){
                _buffer[end++]=c;
                end&=(_capacity-1);
            }
            static inline uint16_t length(){
                return end>=begin ? end-begin : (_capacity-begin)+end;
            }
            static inline void flush(){
                auto counter = _capacity;
                while(counter--)
                    _buffer[counter]=' ';
                end=begin=0;
            }
            static constexpr inline uint16_t capacity() {
                return _capacity;
            }
        };
        static inline BufferInterface _buffer;
        public:
        InStreamInterface(){
            _buffer = BufferInterface();
        }
        static constexpr BufferInterface buffer(){
            return _buffer;
        }
        static inline unsigned char receiveByte(){
            while (!(reference(Registers::R_UCSR0A) & (1 << RXC0)));
            return reference(Registers::R_UDR0);
        }
    };
    struct CallbackInterface{
        using HandleType = void (*)();
        static inline HandleType transmissionCallBack = nullptr;
        static inline HandleType receiveCallBack = nullptr;
        static inline void setTransmissionCallback(HandleType handle){
            transmissionCallBack = handle;
        }
        static inline void setReceiveCallback(HandleType handle){
            receiveCallBack = handle;
        }
        static void receiveHandle(){
            if(receiveCallBack!=nullptr)
                receiveCallBack();
        }
        static void transmissionHandle(){
            if(transmissionCallBack!=nullptr)
                transmissionCallBack();
        }
    };
    struct InterruptInterface{
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
    };
    public:
        using Setting = SettingInterface;
        using Callback = CallbackInterface;
        using Interrupt = InterruptInterface;
        static inline OutStreamInterface out;
        static inline InStreamInterface in;
        UART()
        {
            Setting::defaultSettings();
            out = OutStreamInterface();
            in = InStreamInterface();
        }
};
static inline auto System = UART<64>();
ISR(USART_RX_vect) {
    auto symbol = System.in.receiveByte();
    System.in.buffer().write(symbol);
    UART<System.in.buffer().capacity()>::Callback::receiveHandle();
}
ISR(USART_TX_vect) {
    UART<System.in.buffer().capacity()>::Callback::transmissionHandle();
}
#endif // UART_H
