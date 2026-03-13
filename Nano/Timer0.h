#ifndef TIMER__H
#define TIMER__H
#include <Base.h>
#include <avr/interrupt.h>
#include <Nano.h>
namespace Nano {
    enum class Prescaling{
        NoSource=0,
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

    // template<uint8_t Number>
    class Timer0 : protected Base
    {
        using Handle = void (*)(char);
        static inline Handle callBack = nullptr;
        using HandleOVF = void (*)();
        static inline HandleOVF callBackOVF = nullptr;

        protected:
        static inline void setPrescaling(Prescaling p){
            switch(p){
                case Prescaling::NoSource:
                case Prescaling::_1:
                case Prescaling::_8:
                case Prescaling::_64:
                case Prescaling::_256:
                case Prescaling::_1024:
                case Prescaling::ExternalClockFaling:
                case Prescaling::ExternalClockRising:
                    reference(Registers::R_TCCR0B)|=static_cast<uint8_t>(p);
            };
        }
        static inline void setMode(Mode mode){
            switch(mode){
                case Mode::NORMAL:
                case Mode::CTC:
                case Mode::PWD_FAST:
                case Mode::PWD_PHASE_CORRECT:
                    reference(Registers::R_TCCR0A)=static_cast<uint8_t>(mode);
            }
        }
        static inline void setInterruptMode(InterruptMode mode){
            switch(mode){
                case InterruptMode::OVERFLOW:
                case InterruptMode::COMPARE_A:
                case InterruptMode::COMPARE_B:
                case InterruptMode::ALL:
                    reference(Registers::R_TIMSK0)=static_cast<uint8_t>(mode);
            }
        }
public:
    static inline void setDefaultSettings(){
        cli();
        reference(Registers::R_TCNT0)=0;
        setPrescaling(Prescaling::_64);
        setMode(Mode::NORMAL);
        setInterruptMode(InterruptMode::OVERFLOW);
        sei();
    }
    static inline void setCallbackByMatch(Handle handle){
        callBack = handle;
    }
    static inline void setCallbackByOverFlow(HandleOVF handle){
        callBackOVF = handle;
    }
    static void interruptByMatch(char c){
        callBack(c);
    }
    static void interruptByOverFlow(){
        callBackOVF();
    }
};
}
using Clock = Nano::Timer0;
ISR(TIMER0_COMPA_vect) {
    Clock::interruptByMatch('A');
}
ISR(TIMER0_COMPB_vect) {
    Clock::interruptByMatch('B');
}
ISR(TIMER0_OVF_vect) {
    Clock::interruptByOverFlow();
}
#endif // TIMER__H
