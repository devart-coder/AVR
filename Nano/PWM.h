#ifndef PWM_H
#define PWM_H
#include <inttypes.h>
#include <Timer.h>
#include <Base.h>
#include <Nano.h>
#include <Utils.h>
#include <Delay.h>

namespace Nano{
    using namespace Utils::Templates;

template < class P , class T =  enable_if_t<any_pin_of_v<P::pinNumber, PinD3, PinD5, PinD6, PinD9, PinD10, PinD11>> >
    class PWM : Base{
        private:
            static constexpr uint8_t timerOrder =
                (any_pin_of_v<P::pinNumber, PinD5, PinD6> ) ? 0 :
                    (any_pin_of_v<P::pinNumber, PinD9, PinD10>) ? 1 : 2;
            using timer = Timer<timerOrder>;
        enum class OutMode{
            NORMAL,
            INVERSION
        };
        private:
            static inline void setOutMode(OutMode mode){
                if constexpr(is_same_v<P,PinD6>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A0)|(1<<COM0A1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A1);
                            break;
                    }
                }else if constexpr(is_same_v<P,PinD5>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B0)|(1<<COM0B1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B1);
                            break;
                    }
                }else if constexpr (is_same_v<P,PinD9>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR1A)|=(1<<COM1A0)|(1<<COM1A1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR1A)|=(1<<COM1A1);
                            break;
                    }
                }else if constexpr (is_same_v<P,PinD10>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR1A)|=(1<<COM1B0)|(1<<COM1B1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR1A)|=(1<<COM1B1);
                            break;
                    }
                }else if constexpr (is_same_v<P,PinD11>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR2A)|=(1<<COM2A0)|(1<<COM2A1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR2A)|=(1<<COM2A1);
                            break;
                    }
                }else if constexpr (is_same_v<P,PinD3>){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR2A)|=(1<<COM2B0)|(1<<COM2B1);
                            break;
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR2A)|=(1<<COM2B1);
                            break;
                    }
                }
            }
        public:
            // template<class T>
            //TODO::AppendPairtificateRealizeForuint16_t
            static inline void setDirtyPercent(uint8_t per){
                if ((per < 0)||(per>100))
                    return;
                if constexpr  (is_same_v<P,PinD6>|| is_same_v<P,PinD9>||is_same_v<P,PinD11>)
                    timer::Action::setCounterA((per*0xFF)/100);
                else if constexpr (is_same_v<P,PinD3>||is_same_v<P,PinD5>||is_same_v<P,PinD10>)
                    timer::Action::setCounterB((per*0xFF)/100);
            }
            static inline void setDefaultSettings(){
                cli();
                P::setMode(PinMode::OUTPUT);

                timer::Setting::setPrescaling(Nano::Prescaling::_64);
                timer::Setting::setMode(Mode::PWD_FAST);
                setOutMode(OutMode::NORMAL);

                sei();
            }
    };
    using PWMD3 = PWM<Nano::PinD3>;
    using PWMD5 = PWM<Nano::PinD5>;
    using PWMD6 = PWM<Nano::PinD6>;
    using PWMD9 = PWM<Nano::PinD9>;
    using PWMD11 = PWM<Nano::PinD11>;
}
#endif // PWM_H
