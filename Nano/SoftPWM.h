#ifndef SOFTPWM_H
#define SOFTPWM_H
#include <Timer.h>
#include <Bus.h>
    //SoftPWM::Settings::setMode(NORMAL,INVERSION);
    //SoftPWM::Action::setDirtyPercent(uint8_t );
    //SoftPWM::Action::setDirtyByte(uint8_t );

    template <class BUS>
    class SoftPWM{
        using timer = Timer0;
        class ActionInterface{
            public:
            ActionInterface(){
                BUS::setDirection(0xff);
                timer::Setting::defaultSettings();
                timer::Callback::byMatchA([](){
                    BUS::write(0xff);
                });
                timer::Callback::byMatchB([](){
                    BUS::write(0);
                });
            }
            static inline void start(){
                timer::Action::start();
            }
            static inline void setDirtyPercent(uint8_t p){
                timer::Action::setCounterA((p*0xff)/100);
            }
            static inline void setDirtyByte(uint8_t byte){
                timer::Action::setCounterA(byte);
            }
        };
        public:
            static inline ActionInterface action = ActionInterface();
    };
    template<class... PINS>
    using Soft = SoftPWM<Bus<PINS...>>;

#endif // SOFTPWM_H
