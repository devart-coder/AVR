#ifndef EXTERNALINTERRUPT_H
#define EXTERNALINTERRUPT_H
#include <Utils.h>
#include <Nano.h>
#include <Callable.h>
#include <avr/interrupt.h>//deprecated

namespace Nano {

    enum class TriggerMode{
        LOW_LEVEL,
        ANY_CHANGE,
        FALLING_EDGE,
        RISING_EDGE
    };

    template<class PIN, uint8_t number=PIN::pinNumber, class T = Utils::Templates::enable_if_t<(number == (1<<2)) || ( number == (1<<3))> >
    class ExternalInterrupt : Base{
    protected:
        using HandleType = void(*)();
        static inline HandleType callback = nullptr;
    public:
        static void setCallback(HandleType f ){
            callback=f;
        }
        static void handle(){
            callback();
        }
        public:
        static inline void setTriggerMode(TriggerMode mode){
            if constexpr (number == (1<<2)){
                switch(mode){
                    case TriggerMode::LOW_LEVEL:
                        reference(Registers::R_EICRA)&=~((1<<ISC01)|(1<<ISC00));
                        break;
                    case TriggerMode::ANY_CHANGE:
                        reference(Registers::R_EICRA)&=~(1<<ISC01);
                        reference(Registers::R_EICRA)|=(1<<ISC00);
                        break;
                    case TriggerMode::FALLING_EDGE:
                        reference(Registers::R_EICRA)|=(1<<ISC01);
                        reference(Registers::R_EICRA)&=~(1<<ISC00);
                        break;
                    case TriggerMode::RISING_EDGE:
                        reference(Registers::R_EICRA)|=(1<<ISC01);
                        reference(Registers::R_EICRA)|=(1<<ISC00);
                        break;
                }
            }//INT0
            else{
                switch(mode){
                    case TriggerMode::LOW_LEVEL:
                        reference(Registers::R_EICRA)&=~((1<<ISC11)|(1<<ISC10));
                        break;
                    case TriggerMode::ANY_CHANGE:
                        reference(Registers::R_EICRA)&=~(1<<ISC11);
                        reference(Registers::R_EICRA)|=(1<<ISC10);
                        break;
                    case TriggerMode::FALLING_EDGE:
                        reference(Registers::R_EICRA)|=(1<<ISC11);
                        reference(Registers::R_EICRA)&=~(1<<ISC10);
                        break;
                    case TriggerMode::RISING_EDGE:
                        reference(Registers::R_EICRA)|=(1<<ISC11);
                        reference(Registers::R_EICRA)|=(1<<ISC10);
                        break;
                }
            }//INT1
        }
        static inline void enableInterrupts(){
            if constexpr (number == (1<<2))
                reference(Registers::R_EIMSK)|=(1<<INT0);
            else
                reference(Registers::R_EIMSK)|=(1<<INT1);
        }
    public:
        static inline void setDefaultSettings(){
            cli();
            PIN::setMode(PinMode::INPUT_PULL_UP);
            setTriggerMode(TriggerMode::FALLING_EDGE);
            enableInterrupts();
            sei();
        }
    };

    using EID2 = ExternalInterrupt<PinD2>;
    using EID3 = ExternalInterrupt<PinD3>;

    ISR(INT0_vect){
        EID2::handle();
    }

    ISR(INT1_vect){
        EID3::handle();
    }
}
#endif // EXTERNALINTERRUPT_H
