#ifndef SOFTPWM_H
#define SOFTPWM_H
#include <Timer.h>
#include <Bus.h>
    //SoftPWM::Settings::setMode(NORMAL,INVERSION);

    template <class... PINS>
    class SoftPWM{
        using Timer = Nano::Timer<0>;
        using b = Bus<PINS...>;
        class ActionInterface{
            public:
            ActionInterface(){
                b::setDirection(0xff);
                Timer::Setting::defaultSettings();
                Timer::Callback::byMatchA([](){
                    b::write(0xff);
                });
                Timer::Callback::byMatchB([](){
                    b::write(0);
                });
            }
            static inline void start(){
                Timer::Action::start();
            }
            static inline void setDutyCycle(uint8_t p){
                Timer::Action::setCounterA((p*0xff)/100);
            }
            static inline void setDutyByte(uint8_t byte){
                Timer::Action::setCounterA(byte);
            }
        };
        public:
            static inline ActionInterface action = ActionInterface();
    };

#endif // SOFTPWM_H
