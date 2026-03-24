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

    class Timer : public Callable, protected Base
    {
        private:
            static  inline Prescaling prescaling = Prescaling::_64;
        private:
            struct ActionInterface{
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
                static void setTimerCounter(uint8_t value){
                    reference(Registers::R_TCNT0)=value;
                }
                static const uint8_t timerCounter(){
                    return reference(Registers::R_TCNT0);
                }
                static inline void stop(){
                    setTimerCounter(0);
                    Settings::setPrescaling(Prescaling::NoSource);
                }
                static inline void start(){
                    Settings::setPrescaling(prescaling);
                }
            };
        private://Interruptes
            struct InterruptesInterface{
                static void enableAChannel(){
                    reference(Registers::R_TIMSK0)|=(1<<1);
                }
                static void enableBChannel(){
                    reference(Registers::R_TIMSK0)|=(1<<2);
                }
                static void enableOverFlow(){
                    reference(Registers::R_TIMSK0)|=(1<<0);
                }

                static void disableAChannelInterrupt(){
                    reference(Registers::R_TIMSK0)&=~(1<<1);
                }
                static void disableBChannelInterrupt(){
                    reference(Registers::R_TIMSK0)&=~(1<<2);
                }
                static void disableOverFlowInterrupt(){
                    reference(Registers::R_TIMSK0)&=~(1<<0);
                }
            };
        private://Settings
            struct SettingsInterface{
                static inline void setPrescaling(Prescaling p){
                    reference(Registers::R_TCCR0B)&=~((1<<CS02)|(1<<CS01)|(1<<CS00));
                    switch(p){
                        case Prescaling::NoSource:
                            break;
                        case Prescaling::_1:
                            reference(Registers::R_TCCR0B)|=(1<<CS00);
                            break;
                        case Prescaling::_8:
                            reference(Registers::R_TCCR0B)|=(1<<CS01);
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
                            //TODO::REALIZE
                            break;
                        case Prescaling::ExternalClockRising:
                            //TODO::REALIZE
                            break;
                    };
                }
                static Prescaling getPrescaling();
                static inline void setMode(Mode mode){
                    reference(Registers::R_TCCR0A)=static_cast<uint8_t>(Mode::NORMAL);
                    switch(mode){
                        case Mode::CTC:
                        case Mode::PWD_FAST:
                        case Mode::PWD_PHASE_CORRECT:
                            reference(Registers::R_TCCR0A)|=static_cast<uint8_t>(mode);
                    }
                }
                static inline void setDefaultSettings(){
                    cli();
                    setPrescaling(Prescaling::_64);
                    Settings::setMode(Mode::NORMAL);
                    sei();
                }
            };
        private://Callback
            class CallbackInterface{
                static inline HandleType callACharBack = nullptr;
                static inline HandleType callBCharBack = nullptr;
            public:
                static void setPrescaling(Prescaling p){
                    prescaling = p;
                }
                static void byMatchA(HandleType handle){
                    callACharBack = handle;
                }
                static inline void byMatchB(HandleType handle){
                    callBCharBack = handle;
                }
                static void interruptByMatchA(){
                    callACharBack();
                }
                static void interruptByMatchB(){
                    callBCharBack();
                }
            };
        public :
            using Settings = SettingsInterface;
            using Interruptes = InterruptesInterface;
            using Action = ActionInterface;
            using Callback = CallbackInterface;
        };
    }

    using SystemClock = Nano::Timer;

    ISR(TIMER0_COMPA_vect) {
        SystemClock::Callback::interruptByMatchA();
    }
    ISR(TIMER0_COMPB_vect) {
        SystemClock::Callback::interruptByMatchB();
    }
    ISR(TIMER0_OVF_vect) {
        SystemClock::handle();
    }
#endif // TIMER__H
