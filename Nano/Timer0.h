#ifndef TIMER__H
#define TIMER__H
#include <Nano.h>
#include <Base.h>
#include <Callable.h>
#include <avr/interrupt.h>
namespace Nano {
    using namespace Atmega328p::Bits;
    enum class Prescaling{
        NoSource,
        _1,
        _8,
        _64,
        _256,
        _1024,
        ExternalClockFaling,
        ExternalClockRising
    };
    enum class Mode{
        NORMAL=0,
        CTC=2,
        PWD_FAST=3,
        PWD_PHASE_CORRECT=1
    };
    enum class InterruptMode{
        OVERFLOW=1,
        COMPARE_A=2,
        COMPARE_B=4,
        ALL=7
    };

    class Timer0 : protected Base
    {
    private:
        using HandleType = void(*)();
        static inline HandleType callback = nullptr;
    public:
        static void setCallback(HandleType f ){
            callback=f;
        }
        static void handle(){
            callback();
        }
    private:
        using HandleTypeChar = void (*)();
        static inline HandleTypeChar callACharBack = nullptr;
        static inline HandleTypeChar callBCharBack = nullptr;

        static  inline Prescaling prescaling = Prescaling::_64;
        protected:
        static inline void m_setPrescaling(Prescaling p){
            reference(Registers::R_TCCR0B)&=~((1<<CS02)|(1<<CS01)|(1<<CS00));
            switch(p){
                case Prescaling::NoSource:
                    break;
                case Prescaling::_1:
                    reference(Registers::R_TCCR0B)=(1<<CS00);
                    break;
                case Prescaling::_8:
                    reference(Registers::R_TCCR0B)=(1<<CS01);
                    break;
                case Prescaling::_64:
                    reference(Registers::R_TCCR0B)|= (1<<CS00)|(1<<CS01);
                    break;
                case Prescaling::_256:
                    reference(Registers::R_TCCR0B)=(1<<CS02);
                    break;
                case Prescaling::_1024:
                    reference(Registers::R_TCCR0B)=(1<<CS02)|(1<<CS00);
                    break;
                case Prescaling::ExternalClockFaling:
                    break;
                case Prescaling::ExternalClockRising:
                    break;
            };
        }
        static inline void setMode(Mode mode){
            reference(Registers::R_TCCR0A)=static_cast<uint8_t>(Mode::NORMAL);
            switch(mode){
                case Mode::CTC:
                case Mode::PWD_FAST:
                case Mode::PWD_PHASE_CORRECT:
                    reference(Registers::R_TCCR0A)|=static_cast<uint8_t>(mode);
            }
        }
    public:
        static inline void setInterruptMode(InterruptMode mode){
            reference(Registers::R_TIMSK0)=0;
            switch(mode){
                case InterruptMode::OVERFLOW:
                case InterruptMode::COMPARE_A:
                case InterruptMode::COMPARE_B:
                case InterruptMode::ALL:
                    reference(Registers::R_TIMSK0)|=static_cast<uint8_t>(mode);
            }
        }
    public:
        static inline void setCounterA(uint8_t value){
            reference(Registers::R_OCR0A)=value;
        }
        static inline const uint8_t counterA(){
            return reference(Registers::R_OCR0A);
        }
        static inline void setCounterB(uint8_t value){
            reference(Registers::R_OCR0B)=value;
        }
        static inline const uint8_t counterB(){
            return reference(Registers::R_OCR0B);
        }
        static inline void setDefaultSettings(){
            cli();
            setPrescaling(Prescaling::_64);
            setMode(Mode::NORMAL);
            // setInterruptMode(InterruptMode::COMPARE_A);
            // setInterruptMode(InterruptMode::OVERFLOW);
            // enableOverFlowInterrupt();
            enableAChannelInterrupt();
            enableBChannelInterrupt();
            sei();
        }
        static void resetCounter(){
            reference(Registers::R_TCNT0)=0;
        }
        static void enableAChannelInterrupt(){
            reference(Registers::R_TIMSK0)|=(1<<1);
        }
        static void enableBChannelInterrupt(){
            reference(Registers::R_TIMSK0)|=(1<<2);
        }
        static void enableOverFlowInterrupt(){
            reference(Registers::R_TIMSK0)|=(1<<0);
        }
        //
        static inline void stop(){
            reference(Registers::R_TCNT0)=0;
            m_setPrescaling(Prescaling::NoSource);
        }
        static inline void setPrescaling(Prescaling p){
            prescaling = p;
        }
        static inline void start(){
            reference(Registers::R_TCNT0)=0;
            m_setPrescaling(prescaling);
        }
        //
        static inline void setCallbackByMatchA(HandleTypeChar handle){
            callACharBack = handle;
        }
        static inline void setCallbackByMatchB(HandleTypeChar handle){
            callBCharBack = handle;
        }
        static void interruptByMatchA(){
            callACharBack();
        }
        static void interruptByMatchB(){
            callBCharBack();
        }
        static Prescaling getPrescaling();
    };
}
using SystemClock = Nano::Timer0;
ISR(TIMER0_COMPA_vect) {
    SystemClock::interruptByMatchA();
}
ISR(TIMER0_COMPB_vect) {
    SystemClock::interruptByMatchB();
}
ISR(TIMER0_OVF_vect) {
    SystemClock::handle();
}
#endif // TIMER__H
