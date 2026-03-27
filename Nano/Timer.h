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
        NORMAL,
        CTC,
        PWD_FAST,
        PWD_PHASE_CORRECT
    };

    template <uint8_t number>
    class Timer : public Callable, Base
    {
            static  inline Prescaling prescaling = Prescaling::NoSource;
        private:
            struct ActionInterface{
                static inline void setCounterA(uint8_t value){
                        if constexpr(number == 0){
                            reference(Registers::R_OCR0A)= value;
                        }else if constexpr (number == 1){
                            reference(Registers::R_OCR1AH) = 0;
                            reference(Registers::R_OCR1AL) = value;
                        }else if constexpr (number == 2){
                            reference(Registers::R_OCR2A)=value;
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
                static inline void setCounterB(uint8_t value){
                    if constexpr(number == 0){
                        reference(Registers::R_OCR0B)=value;
                    }else if constexpr (number == 1){
                        reference(Registers::R_OCR1BH) = 0;
                        reference(Registers::R_OCR1BL) = value;
                    }else if constexpr (number == 2){
                        reference(Registers::R_OCR2B)= 0xFF;
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
                static void setTimerCounter(uint8_t value){
                    if constexpr(number == 0){
                        reference(Registers::R_TCNT0)  = value;
                    }else if constexpr (number == 1){
                        reference(Registers::R_TCNT1H) = 0;//static_cast<uint8_t>(value >> 8);
                        reference(Registers::R_TCNT1L) = value;
                    }else if constexpr (number == 2){
                        reference(Registers::R_TCNT2)  = value;
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
                    Setting::setUpPrescaling(prescaling);
                }
                static Prescaling getPrescaling()
                {
                    return prescaling;
                }
            };
            class InterruptesInterface{
                template<char c>
                static constexpr void enableChannel(bool&& flag){
                    if constexpr(number == 0){
                        if constexpr (c == 'A')
                            flag ?
                                reference(Registers::R_TIMSK0)|=(1<< OCIE0A) :
                                    reference(Registers::R_TIMSK0)&=~(1<< OCIE0A);

                        else if constexpr (c=='B')
                            flag ?
                                reference(Registers::R_TIMSK0)|=(1<< OCIE0B) :
                                    reference(Registers::R_TIMSK0)&=~(1<< OCIE0B);
                        else if constexpr (c=='O')
                            flag ?
                                reference(Registers::R_TIMSK0)|=(1<<0) :
                                    reference(Registers::R_TIMSK0)&=~(1<<0);
                    }
                    else if constexpr(number == 1){
                        if constexpr (c == 'A')
                            flag ?
                                reference(Registers::R_TIMSK1)|=(1<< OCIE1A) :
                                    reference(Registers::R_TIMSK1)&=~(1<< OCIE1A);
                        else if constexpr (c=='B')
                            flag ?
                                reference(Registers::R_TIMSK1)|=(1<< OCIE1B) :
                                    reference(Registers::R_TIMSK1)&=~(1<< OCIE1B);
                        else if constexpr (c=='O')
                            flag ?
                                reference(Registers::R_TIMSK1)|=(1<<0) :
                                    reference(Registers::R_TIMSK1)&=~(1<<0);
                    }
                    else if constexpr(number == 2){
                        if constexpr (c == 'A')
                            flag ?
                                reference(Registers::R_TIMSK2)|=(1<< OCIE2A):
                                    reference(Registers::R_TIMSK2)&=~(1<< OCIE2A);
                        else if constexpr (c=='B')
                            flag ?
                                reference(Registers::R_TIMSK2)|=(1<< OCIE2B):
                                    reference(Registers::R_TIMSK2)&=~(1<< OCIE2B);
                        else if constexpr (c=='O')
                            flag ?
                                reference(Registers::R_TIMSK2)|=(1<<0):
                                    reference(Registers::R_TIMSK2)&=~(1<<0);
                    }
                }
                public:
                static void enableAChannel(){
                    enableChannel<'A'>(true);
                }
                static void enableBChannel(){
                    enableChannel<'B'>(true);
                }
                static void enableOverFlow(){
                    enableChannel<'O'>(true);
                }

                static void disableAChannelInterrupt(){
                    enableChannel<'A'>(false);
                }
                static void disableBChannelInterrupt(){
                    enableChannel<'B'>(false);
                }
                static void disableOverFlowInterrupt(){
                    enableChannel<'O'>(false);
                }
            };
            class SettingsInterface{
                template<uint8_t _1, uint8_t _2, uint8_t _3>
                static void assignPrescalingBits(uint8_t&& f=0, uint8_t&& s=0, uint8_t&& t=0){
                    if constexpr (number == 0)
                        reference(Registers::R_TCCR0B)|=(1<<_1)|(1<<f);
                    else if constexpr(number == 1)
                        reference(Registers::R_TCCR1B)|=(1<<_2)|(1<<s);
                    else if constexpr(number == 2)
                        reference(Registers::R_TCCR2B)|=(1<<_3)|(1<<t);
                }
                template<uint8_t _1, uint8_t _2, uint8_t _3>
                static void assignModeBits(uint8_t&& f=0, uint8_t&& s=0, uint8_t&& t=0){
                    if constexpr (number == 0)
                        reference(Registers::R_TCCR0A)|=(1<<_1)|(1<<f);
                    else if constexpr(number == 1)
                        reference(Registers::R_TCCR1A)|=(1<<_2)|(1<<s);
                    else if constexpr(number == 2)
                        reference(Registers::R_TCCR2A)|=(1<<_3)|(1<<t);
                }

                template<uint8_t _1, uint8_t _2, uint8_t _3>
                static void resetModeBits(uint8_t&& f=0, uint8_t&& s=0, uint8_t&& t=0){
                    if constexpr (number == 0)
                        reference(Registers::R_TCCR0A)&=~((1<<_1)|(1<<f));
                    else if constexpr(number == 1)
                        reference(Registers::R_TCCR1A)&=~((1<<_2)|(1<<s));
                    else if constexpr(number == 2)
                        reference(Registers::R_TCCR2A)&=~((1<<_3)|(1<<t));
                }
                public:
                static inline void setUpPrescaling(Prescaling p){
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
                            assignPrescalingBits<CS00,CS10,CS20>();
                            break;
                        case Prescaling::_8:
                            assignPrescalingBits<CS01,CS11,CS21>();
                            break;
                        case Prescaling::_64:
                            assignPrescalingBits<CS00,CS10,CS20>(CS01,CS11,CS21);
                            break;
                        case Prescaling::_256:
                            assignPrescalingBits<CS02,CS12,CS22>();
                            break;
                        case Prescaling::_1024:
                            assignPrescalingBits<CS02,CS12,CS22>(CS00,CS10,CS20);
                            break;
                        case Prescaling::ExternalClockFaling:
                            //TODO::REALIZE
                            break;
                        case Prescaling::ExternalClockRising:
                            //TODO::REALIZE
                            break;
                    };
                }
                static void setPrescaling(Prescaling p){
                    prescaling = p;
                }
                static inline void setMode(Mode mode){
                    resetModeBits<WGM01,WGM11, WGM21> (WGM00, WGM20, WGM20);
                    switch(mode){
                        case Mode::NORMAL:
                            break;
                        case Mode::PWD_PHASE_CORRECT:
                            assignModeBits<WGM00, WGM10, WGM20>();
                            break;
                        case Mode::CTC:
                            assignModeBits<WGM01, WGM11, WGM21>();
                            break;
                        case Mode::PWD_FAST:
                            assignModeBits<WGM01, WGM11, WGM21>( WGM00, WGM10, WGM20);
                            break;
                        };
                }
                static inline void defaultSettings(){
                    cli();
                    setPrescaling(Prescaling::_64);
                    Setting::setMode(Mode::NORMAL);
                    sei();
                }
            };
            class CallbackInterface{
                static inline HandleType callBackAChannel = nullptr;
                static inline HandleType callBackBChannel = nullptr;
            public:

                static void byMatchA(HandleType handle){
                    Interrupte::enableAChannel();
                    callBackAChannel = handle;
                }
                static inline void byMatchB(HandleType handle){
                    Interrupte::enableBChannel();
                    callBackBChannel = handle;
                }
                static inline void interruptByMatchA(){
                    callBackAChannel();
                }
                static inline void interruptByMatchB(){
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
