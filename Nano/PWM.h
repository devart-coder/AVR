#ifndef PWM_H
#define PWM_H
#include <inttypes.h>
#include <Timer.h>
#include <Base.h>
#include <Nano.h>
#include <Utils.h>
#include <Delay.h>

//TODO:: For Timer<1> define new method : 'setMaxTimerCounter()'
namespace Nano{
    using namespace Utils::Templates;
    enum class OutMode{
        NORMAL,
        INVERSION
    };
template < class P , class T =  enable_if_t<any_pin_of_v<P::pinNumber, PinD3, PinD5, PinD6, PinD9, PinD10, PinD11>> >
    class PWM : Base{
        private:
            static constexpr uint8_t timerOrder =
                (any_pin_of_v<P::pinNumber, PinD5, PinD6> ) ? 0 :
                    (any_pin_of_v<P::pinNumber, PinD9, PinD10>) ? 1 : 2;
            using timer = Timer<timerOrder>;

        private:
            template<Registers reg, uint8_t _1, uint8_t _2>
            static void setFirstBitOrAll( OutMode mode ){
                mode == OutMode::NORMAL ?
                    reference(reg)|=(1<<_1) :
                        reference(reg)|=(1<<_1)|(1<<_2);
            }
        private:
            static inline void setOutMode(OutMode mode){
                reference(Registers::R_TCCR0A)&=~((1<<COM0A1)|(1<<COM0A0)|(1<<COM0B1)|(1<<COM0B0));
                if constexpr(is_same_v<P,PinD6>){
                    setFirstBitOrAll<Registers::R_TCCR0A, COM0A1,COM0A0>(mode);
                }else if constexpr(is_same_v<P,PinD5>){
                    setFirstBitOrAll<Registers::R_TCCR0A,COM0B1,COM0B0>(mode);
                }else if constexpr (is_same_v<P,PinD9>){
                    setFirstBitOrAll<Registers::R_TCCR1A,COM1A1,COM1A0>(mode);
                }else if constexpr (is_same_v<P,PinD10>){
                    setFirstBitOrAll<Registers::R_TCCR1A,COM1B1,COM1B0>(mode);
                }else if constexpr (is_same_v<P,PinD11>){
                    setFirstBitOrAll<Registers::R_TCCR2A,COM2A1,COM2B0>(mode);
                }else if constexpr (is_same_v<P,PinD3>){
                    setFirstBitOrAll<Registers::R_TCCR2A,COM2B1,COM2B0>(mode);
                }
            }
        public:
            static inline void setDutyCycle(uint8_t per){
                static_assert((per < 0)||(per>100),"Dirty percent is not correct");
                if constexpr  (is_same_v<P,PinD6>||is_same_v<P,PinD9>||is_same_v<P,PinD11>)
                    timer::Action::setCounterA((per*0xFF)/100);
                else if constexpr (is_same_v<P,PinD3>||is_same_v<P,PinD5>||is_same_v<P,PinD10>)
                    timer::Action::setCounterB((per*0xFF)/100);
            }
            static inline void setDutyNumber(uint8_t number){
                if constexpr  (is_same_v<P,PinD6>||is_same_v<P,PinD9>||is_same_v<P,PinD11>)
                    timer::Action::setCounterA(number);
                else if constexpr (is_same_v<P,PinD3>||is_same_v<P,PinD5>||is_same_v<P,PinD10>)
                    timer::Action::setCounterB(number);
            }
            static inline void setDefaultSettings(){
                cli();
                P::setMode(PinMode::OUTPUT);
                timer::Setting::setPrescaling(Nano::Prescaling::_64);
                timer::Setting::setMode(Mode::PWD_FAST);
                setOutMode(OutMode::NORMAL);
                timer::Action::start();
                sei();
            }
    };
    using PWMD3  = PWM<Nano::PinD3>;
    using PWMD5  = PWM<Nano::PinD5>;
    using PWMD6  = PWM<Nano::PinD6>;
    using PWMD9  = PWM<Nano::PinD9>;
    using PWMD11 = PWM<Nano::PinD11>;
}
#endif // PWM_H
