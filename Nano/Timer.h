#ifndef TIMER__H
#define TIMER__H
#include <Nano.h>
#include <Base.h>
#include <Callable.h>
#include <avr/interrupt.h>
#include <Utils.h>
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

    template <uint8_t number>
    class Timer : public Callable, protected Base
    {
        private:
            static  inline Prescaling prescaling = Prescaling::_64;
        private:
            struct ActionInterface{
                template<class T>
                static inline void setCounterA(T value){
                    if constexpr (Utils::Templates::is_same_v<T,uint8_t> || Utils::Templates::is_same_v<T,int>){
                        if constexpr(number == 0){
                            reference(Registers::R_OCR0A)= value;
                        }else if constexpr (number == 1){
                            reference(Registers::R_OCR1AH) = 0;
                            reference(Registers::R_OCR1AL) = value;
                        }else if constexpr (number == 2){
                            reference(Registers::R_OCR2A)=value;
                        }
                    }
                    if constexpr (Utils::Templates::is_same_v<T,uint16_t> || Utils::Templates::is_same_v<T,int16_t>){
                        if constexpr (number == 1){
                            reference(Registers::R_OCR1AH) = static_cast<uint8_t>(value >> 8);
                            reference(Registers::R_OCR1AL) = static_cast<uint8_t>(value & 0xFF);
                        }
                    }
                }

                static inline const uint16_t counterA(){
                    if constexpr(number == 0){
                        return reference(Registers::R_OCR0A);
                    }else if constexpr (number == 1){
                        auto l = reference(Registers::R_OCR1AL);
                        auto h = reference(Registers::R_OCR1AH);
                        return ((static_cast<uint16_t>(h) << 8)|l);
                    }else if constexpr (number == 2){
                        return reference(Registers::R_OCR2A);
                    }
                }
                static inline void setCounterB(uint16_t value){
                    if constexpr(number == 0){
                        reference(Registers::R_OCR0B)=(value & 0xFF);
                    }else if constexpr (number == 1){
                        reference(Registers::R_OCR1BH)=(value >> 8);
                        reference(Registers::R_OCR1BL)=(value & 0xFF);
                    }else if constexpr (number == 2){
                        reference(Registers::R_OCR2B)=(value & 0xFF);
                    }
                }
                static inline const uint16_t counterB(){
                    if constexpr(number == 0){
                        return reference(Registers::R_OCR0B);
                    }else if constexpr (number == 1){
                        auto l = reference(Registers::R_OCR1BL);
                        auto h = reference(Registers::R_OCR1BH);
                        return ((static_cast<uint16_t>(h) << 8)|l);
                    }else if constexpr (number == 2){
                        return reference(Registers::R_OCR2B);
                    }
                }
                static void setTimerCounter(uint16_t value){
                    if constexpr(number == 0){
                        reference(Registers::R_TCNT0) = (value & 0xFF);
                    }else if constexpr (number == 1){
                        reference(Registers::R_TCNT1H)=(value >> 8);
                        reference(Registers::R_TCNT1L)=(value & 0xFF);
                    }else if constexpr (number == 2){
                        reference(Registers::R_TCNT2)=(value & 0xFF);
                    }
                }
                static const uint16_t timerCounter(){
                    if constexpr(number == 0){
                        return reference(Registers::R_TCNT0);
                    }else if constexpr (number == 1){
                        auto l = reference(Registers::R_TCNT1L);
                        auto h = reference(Registers::R_TCNT1H);
                        return ((static_cast<uint16_t>(h) << 8)|l);
                    }else if constexpr (number == 2){
                        return reference(Registers::R_TCNT2);
                    }
                }
                static inline void stop(){
                    setTimerCounter(0);
                    Setting::setPrescaling(Prescaling::NoSource);
                }
                static inline void start(){
                    Setting::setPrescaling(prescaling);
                }
            };
        private://Interruptes
            struct InterruptesInterface{
                static void enableAChannel(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)|=(1<< OCIE0A);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)|=(1<< OCIE1A);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)|=(1<< OCIE2A);
                }
                static void enableBChannel(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)|=(1<< OCIE0B);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)|=(1<< OCIE1B);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)|=(1<< OCIE2B);
                }
                static void enableOverFlow(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)|=(1<<0);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)|=(1<<0);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)|=(1<<0);
                }

                static void disableAChannelInterrupt(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)&=~(1<< OCIE0A);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)&=~(1<< OCIE1A);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)&=~(1<< OCIE2A);
                }
                static void disableBChannelInterrupt(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)&=~(1<< OCIE0B);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)&=~(1<< OCIE1B);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)&=~(1<< OCIE2B);
                }
                static void disableOverFlowInterrupt(){
                    if constexpr(number == 0)
                        reference(Registers::R_TIMSK0)&=~(1<<0);
                    else if constexpr(number == 1)
                        reference(Registers::R_TIMSK1)&=~(1<<0);
                    else if constexpr(number == 2)
                        reference(Registers::R_TIMSK2)&=~(1<<0);
                }
            };
        private://Settings
            struct SettingsInterface{
                static inline void setPrescaling(Prescaling p){
                    if constexpr (number == 0)
                        reference(Registers::R_TCCR0B)&=~((1<<CS02)|(1<<CS01)|(1<<CS00));
                    else if constexpr (number == 1)
                        reference(Registers::R_TCCR1B)&=~((1<<CS12)|(1<<CS11)|(1<<CS10));
                    else if constexpr(number == 2)
                        reference(Registers::R_TCCR2B)&=~((1<<CS22)|(1<<CS21)|(1<<CS20));
                    switch(p){
                        case Prescaling::NoSource:
                            break;
                        case Prescaling::_1:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0B)|=(1<<CS00);
                            else if constexpr(number == 1)
                                reference(Registers::R_TCCR1B)|=(1<<CS10);
                            else if constexpr(number == 2)
                                reference(Registers::R_TCCR2B)|=(1<<CS20);
                            break;
                        case Prescaling::_8:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0B)|=(1<<CS01);
                            else if constexpr(number == 1)
                                reference(Registers::R_TCCR1B)|=(1<<CS11);
                            else if constexpr(number == 2)
                                reference(Registers::R_TCCR2B)|=(1<<CS21);
                            break;
                        case Prescaling::_64:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0B)|=(1<<CS00)|(1<<CS01);
                            else if constexpr(number == 1)
                                reference(Registers::R_TCCR1B)|=(1<<CS10)|(1<<CS11);
                            else if constexpr(number == 2)
                                reference(Registers::R_TCCR2B)|=(1<<CS20)|(1<<CS21);
                            break;
                        case Prescaling::_256:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0B)|=(1<<CS02);
                            else if constexpr(number == 1)
                                reference(Registers::R_TCCR1B)|=(1<<CS12);
                            else if constexpr(number == 2)
                                reference(Registers::R_TCCR2B)|=(1<<CS22);
                            break;
                        case Prescaling::_1024:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0B)|=(1<<CS02)|(1<<CS00);
                            else if constexpr(number == 1)
                                reference(Registers::R_TCCR1B)|=(1<<CS12)|(1<<CS10);
                            else if constexpr(number == 2)
                                reference(Registers::R_TCCR2B)|=(1<<CS22)|(1<<CS20);
                            break;
                        case Prescaling::ExternalClockFaling:
                            //TODO::REALIZE
                            break;
                        case Prescaling::ExternalClockRising:
                            //TODO::REALIZE
                            break;
                    };
                }
                static Prescaling getPrescaling()
                {
                    return prescaling;
                }
                static inline void setMode(Mode mode){
                    // if constexpr (number == 0)
                        // reference(Registers::R_TCCR0A)=static_cast<uint8_t>(Mode::NORMAL);
                    // if constexpr (number == 1)
                        // reference(Registers::R_TCCR1A)=static_cast<uint8_t>(Mode::NORMAL);
                    // if constexpr (number == 2)
                        // reference(Registers::R_TCCR2A)=static_cast<uint8_t>(Mode::NORMAL);
                    switch(mode){
                        case Mode::PWD_FAST:
                            if constexpr (number == 0)
                                reference(Registers::R_TCCR0A)|=static_cast<uint8_t>(mode);
                            if constexpr (number == 1)
                                reference(Registers::R_TCCR1A)|=static_cast<uint8_t>(mode);
                            if constexpr (number == 2)
                                reference(Registers::R_TCCR2A)|=(1<<WGM20)|(1<<WGM20);
                            break;
                        case Mode::CTC:
                            break;
                        case Mode::PWD_PHASE_CORRECT:
                            break;
                        };
                }
                static inline void setDefaultSettings(){
                    cli();
                    setPrescaling(Prescaling::_64);
                    Setting::setMode(Mode::NORMAL);
                    sei();
                }
            };
        private://Callback
            class CallbackInterface{
                static inline HandleType callBackAChannel = nullptr;
                static inline HandleType callBackBChannel = nullptr;
            public:
                static void setPrescaling(Prescaling p){
                    prescaling = p;
                }
                static void byMatchA(HandleType handle){
                    Interrupte::enableAChannel();
                    callBackAChannel = handle;
                }
                static inline void byMatchB(HandleType handle){
                    Interrupte::enableBChannel();
                    callBackBChannel = handle;
                }
                static void interruptByMatchA(){
                    callBackAChannel();
                }
                static void interruptByMatchB(){
                    callBackBChannel();
                }
            };
        public :
            using Setting = SettingsInterface;
            using Interrupte = InterruptesInterface;
            using Action = ActionInterface;
            using Callback = CallbackInterface;
        };
    }

    using Timer0 = Nano::Timer<0>;
    using Timer1 = Nano::Timer<1>;
    using Timer2 = Nano::Timer<2>;

    ISR(TIMER0_COMPA_vect) {
        Timer0::Callback::interruptByMatchA();
    }
    ISR(TIMER0_COMPB_vect) {
        Timer0::Callback::interruptByMatchB();
    }
    ISR(TIMER0_OVF_vect) {
        Timer0::handle();
    }
    ISR(TIMER1_COMPA_vect) {
        Timer1::Callback::interruptByMatchA();
    }
    ISR(TIMER1_COMPB_vect) {
        Timer1::Callback::interruptByMatchB();
    }
    ISR(TIMER1_OVF_vect) {
        Timer1::handle();
    }
    ISR(TIMER2_COMPA_vect) {
        Timer2::Callback::interruptByMatchA();
    }
    ISR(TIMER2_COMPB_vect) {
        Timer2::Callback::interruptByMatchB();
    }
    ISR(TIMER2_OVF_vect) {
        Timer2::handle();
    }
#endif // TIMER__H
