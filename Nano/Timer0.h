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

    class Timer0 : public Callable<void(*)()>, protected Base
    {
        using HandleType = void (*)(char);
        static inline HandleType callBack = nullptr;
        static Prescaling prescaling;
        protected:
        static inline void m_setPrescaling(Prescaling p){
            switch(p){
                case Prescaling::NoSource:
                    reference(Registers::R_TCCR0B)&=~((1<<CS02)|(1<<CS01)|(1<<CS00));
                    break;
                case Prescaling::_1:
                    reference(Registers::R_TCCR0B)=(~(1<<CS02) & ~(1<<CS01))|(1<<CS00);
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::_8:
                    reference(Registers::R_TCCR0B)=(~(1<<CS02) & ~(1<<CS00))|(1<<CS01);
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::_64:
                    reference(Registers::R_TCCR0B)=~(1<<CS02) & ((1<<CS00)|(1<<CS01));
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::_256:
                    reference(Registers::R_TCCR0B)=(~(1<<CS01) & ~(1<<CS00))|(1<<CS02);
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::_1024:
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::ExternalClockFaling:
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
                case Prescaling::ExternalClockRising:
                    // reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
                    break;
            };
        }
        static inline void setMode(Mode mode){
            switch(mode){
                case Mode::NORMAL:
                case Mode::CTC:
                case Mode::PWD_FAST:
                case Mode::PWD_PHASE_CORRECT:
                    reference(Registers::R_TCCR0A)|=static_cast<uint8_t>(mode);
            }
        }
        static inline void setInterruptMode(InterruptMode mode){
            switch(mode){
                case InterruptMode::OVERFLOW:
                case InterruptMode::COMPARE_A:
                case InterruptMode::COMPARE_B:
                case InterruptMode::ALL:
                    reference(Registers::R_TIMSK0)|=static_cast<uint8_t>(mode);
            }
        }
    public:
        static inline void setDefaultSettings(){
            cli();
            setPrescaling(Prescaling::_64);
            setMode(Mode::NORMAL);
            setInterruptMode(InterruptMode::OVERFLOW);
            sei();
        }

        //
        static inline void stop(){
            m_setPrescaling(Prescaling::NoSource);
            reference(Registers::R_TCNT0)=0;
        }
        static inline void setPrescaling(Prescaling p){
            prescaling = p;
        }
        static inline void start(){
            reference(Registers::R_TCNT0)=0;
            m_setPrescaling(prescaling);
        }
        //
        static inline void setCallbackByMatch(HandleType handle){
            callBack = handle;
        }
        static void interruptByMatch(char c){
            callBack(c);
        }
        static Prescaling getPrescaling();
    };
}
using SystemClock = Nano::Timer0;
ISR(TIMER0_COMPA_vect) {
    SystemClock::interruptByMatch('A');
}
ISR(TIMER0_COMPB_vect) {
    SystemClock::interruptByMatch('B');
}
ISR(TIMER0_OVF_vect) {
    SystemClock::handle();
}
#endif // TIMER__H
