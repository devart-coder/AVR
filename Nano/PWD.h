#ifndef PWD_H
#define PWD_H
#include <inttypes.h>
#include <Timer0.h>
#include <Base.h>
#include <Nano.h>
#include <Utils.h>
namespace Nano{
    using namespace Utils::Templates;
    template < class P , uint8_t number = P::pinNumber, class T =  enable_if_t<(number == 5)||(number == 6)>>
    class PWD : private Timer0{
        enum class OutMode{
            NORMAL,
            INVERSION
        };
        private:
            static inline void setOutMode(OutMode mode){
                if(P::pinNumber == 5){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B1);
                    }
                }
                if(P::pinNumber == 6){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A1);
                    }
                }
            }
        public:
            static inline void setDirtyPercent(uint8_t per){
                if ((per < 0)||(per>100))
                    return;
                if (P::pinNumber == 6)
                    reference(Registers::R_OCR0A)= static_cast<uint8_t>((per*255)/100);
                if (P::pinNumber == 5)
                    reference(Registers::R_OCR0B)= static_cast<uint8_t>((per*255)/100);
            }
            static inline void setDefaultSettings(){
                P::setMode(P::Direction::OUTPUT);
                setOutMode(OutMode::NORMAL);
                setMode(Mode::PWD_FAST);
                setPrescaling(Nano::Prescaling::_64);//1ms for 16MHz
            }
    };
    using PWDD5 = PWD<Nano::PinD5>;
    using PWDD6 = PWD<Nano::PinD6>;
}
#endif // PWD_H
