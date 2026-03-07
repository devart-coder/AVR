#ifndef PWD_H
#define PWD_H
#include <inttypes.h>
#include <Nano.h>
#include <Base.h>
namespace Nano{
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
    template <class P>
    class PWD : private Base{
        enum class OutMode{
            NORMAL,
            INVERSION
        };
        enum class PWDMode{
            FAST,
            PHASE_CORRECT
        };
        private:
            static inline void setPrescaling(Prescaling m){
                switch(m){
                    case Prescaling::NoSource:
                        reference(Registers::R_TCCR0B)|=0;
                        break;
                    case Prescaling::_1:
                        reference(Registers::R_TCCR0B)|=1;
                        break;
                    case Prescaling::_8:
                        reference(Registers::R_TCCR0B)|=2;
                        break;
                    case Prescaling::_64:
                        reference(Registers::R_TCCR0B)|=3;
                        break;
                    case Prescaling::_256:
                        reference(Registers::R_TCCR0B)|=4;
                        break;
                    case Prescaling::_1024:
                        reference(Registers::R_TCCR0B)|=5;
                        break;
                    case Prescaling::ExternalClockFaling:
                        reference(Registers::R_TCCR0B)|=6;
                        break;
                    case Prescaling::ExternalClockRising:
                        reference(Registers::R_TCCR0B)|=7;
                        break;
                };
            }
            static inline void setOutMode(OutMode mode){
                if(P::pinNumber == 5){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0A1);
                    }
                }
                if(P::pinNumber == 6){
                    switch(mode){
                        case OutMode::INVERSION:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B0);
                        case OutMode::NORMAL:
                            reference(Registers::R_TCCR0A)|=(1<<COM0B1);
                    }
                }
            }
            static inline void setPWDMode(PWDMode mode){
                switch(mode){
                    case PWDMode::FAST:
                        reference(Registers::R_TCCR0A)|=(1<<WGM00);
                    case PWDMode::PHASE_CORRECT:
                        reference(Registers::R_TCCR0A)|=(1<<WGM01);
                }
            }
        public:
            static inline void setDirtyPercent(uint8_t per){
                if ((per < 0)||(per>100))
                    return;
                if (P::pinNumber == 6)
                    reference(Registers::R_OCR0A)= static_cast<uint8_t>((per*255)/100);
                if (P::pinNumber == 6)
                    reference(Registers::R_OCR0B)= static_cast<uint8_t>((per*255)/100);
            }
            static inline void setDefaultSettings(){
                P::setMode(P::Direction::OUTPUT);
                setOutMode(OutMode::NORMAL);
                setPWDMode(PWDMode::FAST);
                setPrescaling(Prescaling::_64);//1ms for 16MHz
            }
    };
    using PWDD5 = PWD<Nano::PinD5>;
    using PWDD6 = PWD<Nano::PinD6>;
}
#endif // PWD_H
