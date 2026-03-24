#ifndef CNC_H
#define CNC_H
#include <Nano.h>
#include <Place.h>
namespace CNC{
    using XDir  = Nano::PinD2;
    using XStep = Nano::PinD5;

    using YDir  = Nano::PinD3;
    using YStep = Nano::PinD6;

    using ZDir  = Nano::PinD4;
    using ZStep = Nano::PinD7;

    //Pattern::Singletone
    class Tool{
        Place place;
        //uint32_t Zposition;
        //uint32_t speed

        //Gcommand();

        //Place:
        //rightTo();
        //leftTo();
        //upTo();
        //downTo();

        //Tool:
        //upTo();
        //downTo();
        //z()const;
    };
}
#endif // CNC_H
