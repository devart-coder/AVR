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
    template < class P , class T =  enable_if_t< (pin_with_number<P,5>::value || pin_with_number<P,6>::value)> >
    class PWM : Timer0{
        enum class OutMode{
            NORMAL,
            INVERSION
        };
        private:
            static inline void setOutMode(OutMode mode){
                if(P::pinNumber == (1<<6)){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A1);
                    }
                }
                if(P::pinNumber == (1<<5)){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B1);
                    }
                }
            }
        public:
            static inline void setDirtyPercent(uint8_t per){
                if ((per < 0)||(per>100))
                    return;
                if constexpr  (P::pinNumber == (1<<6))
                    reference(Registers::R_OCR0A)= static_cast<uint8_t>((per*255)/100);
                if constexpr (P::pinNumber == (1<<5))
                    reference(Registers::R_OCR0B)= static_cast<uint8_t>((per*255)/100);
            }
            static inline void setDefaultSettings(){
                P::setDirection(Direction::OUTPUT);
                setOutMode(OutMode::NORMAL);
                setMode(Mode::PWD_FAST);
                setPrescaling(Nano::Prescaling::_64);//1ms for 16MHz
            }
    };
    using PWMD5 = PWM<Nano::PinD5>;
    using PWMD6 = PWM<Nano::PinD6>;

    template<class PIN, class T = Utils::Templates::enable_if_t<is_pin<PIN>::value> >
    static void programmPWD(uint32_t dirtyCircle, uint32_t time){
        PIN::setHigh();
        delayMs(dirtyCircle);
        PIN::setLow();
        delayMs(time - dirtyCircle);
    }
}
#endif // PWM_H
