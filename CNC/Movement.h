#ifndef MODEMENT_H
#define MODEMENT_H
#include <Nano.h>
#include <Delay.h>
/*
    Axis direction declarative:

  |		   X		^
--.-------->		|
  |					|
  |					|
  |					.
Y v				Z	|




*/
class Movement{
    static constexpr uint8_t defaultDelay = 50 ;
    template<class PIN>
    static constexpr void makeStep(){
        PIN::setHigh();
        delayUs(defaultDelay);
        PIN::setLow();
        delayUs(defaultDelay);
    }
    class AxisX{
            using XDir  = Nano::PinD2;
            using XStep = Nano::PinD5;
        public:
            AxisX() {
                XDir::setMode(PinMode::OUTPUT);
                XStep::setMode(PinMode::OUTPUT);
            }
            static inline void right(){
                XDir::setHigh();
            }
            static inline void left(){
                XDir::setLow();
            }
            static inline void step(){
                makeStep<XStep>();
            }
            static inline void steps(uint32_t value){
                while(value--)
                    step();
            }
    };
    class AxisY{
            using YDir  = Nano::PinD3;
            using YStep = Nano::PinD6;
        public:
            AxisY(){
                YDir::setMode(PinMode::OUTPUT);
                YStep::setMode(PinMode::OUTPUT);
            }
            static inline void up(){
                YDir::setHigh();
            }
            static inline void down(){
                YDir::setLow();
            }
            static inline void step(){
                makeStep<YStep>();
            }
            static inline void steps(uint32_t value){
                while(value--)
                    step();
            }
    };
    class AxisZ{
            using ZDir  = Nano::PinD4;
            using ZStep = Nano::PinD7;
        public:
            AxisZ(){
                ZDir::setMode(PinMode::OUTPUT);
                ZStep::setMode(PinMode::OUTPUT);
            }
            static inline void up(){
                ZDir::setHigh();
            }
            static inline void down(){
                ZDir::setLow();
            }
            static inline void step(){
                makeStep<ZStep>();
            }
            static inline void steps(uint32_t value){
                while(value--)
                    step();
            }
    };
    public:
        static inline AxisX x = AxisX();
        static inline AxisY y = AxisY();
        static inline AxisZ z = AxisZ();
};
#endif // MODEMENT_H
