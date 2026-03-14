#ifndef EXTERNALINTERRUPT_H
#define EXTERNALINTERRUPT_H
#include <Utils.h>
#include <Nano.h>
#include <Callable.h>
#include <avr/interrupt.h>//deprecated

namespace Nano {
    using namespace Utils::Templates;

    enum class TriggerMode{
        LOW_LEVEL,
        ANY_CHANGE,
        FALLING_EDGE,
        RISING_EDGE
    };

    template<class PIN, uint8_t number=PIN::pinNumber, class T = enable_if_t<(number == (1<<2)) ||( number == (1<<3))> >
    class ExternalInterrupt : public Callable , private Base{
        static inline void setTriggerMode(TriggerMode mode){
            auto eicra = reference(Registers::R_EICRA);
            if constexpr (number == 2){
                switch(mode){
                    case TriggerMode::LOW_LEVEL:
                        eicra&=~((1<<ISC01)|(1<<ISC00));
                        break;
                    case TriggerMode::ANY_CHANGE:
                        eicra|=(1<<ISC00);
                        break;
                    case TriggerMode::FALLING_EDGE:
                        eicra|=(1<<ISC01);
                        break;
                    case TriggerMode::RISING_EDGE:
                        eicra|=(1<<ISC01)|(1<<ISC00);
                        break;
                }
            }//INT0
            else{
                switch(mode){
                    case TriggerMode::LOW_LEVEL:
                        eicra&=~((1<<ISC11)|(1<<ISC10));
                        break;
                    case TriggerMode::ANY_CHANGE:
                        eicra|=(1<<ISC10);
                        break;
                    case TriggerMode::FALLING_EDGE:
                        eicra|=(1<<ISC11);
                        break;
                    case TriggerMode::RISING_EDGE:
                        eicra|=(1<<ISC11)|(1<<ISC10);
                        break;
                }
            }//INT1
        }
        static inline void enableInterrupts(){
            switch(number){
            case 2:
                reference(Registers::R_EIMSK)|=(1<<INT0);
                break;
            case 3:
                reference(Registers::R_EIMSK)|=(1<<INT1);
                break;
            }
        }
    public:
        static inline void setDefaultSettings(){
            cli();
            PIN::setMode(PIN::Direction::INPUT);
            PIN::setHigh();
            setTriggerMode(TriggerMode::LOW_LEVEL);
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
