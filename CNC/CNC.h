#ifndef CNC_H
#define CNC_H
#include <Nano.h>
namespace CNC{
    using XDir  = Nano::PinD2;
    using XStep = Nano::PinD5;

    using YDir  = Nano::PinD3;
    using YStep = Nano::PinD6;

    using ZDir  = Nano::PinD4;
    using ZStep = Nano::PinD7;

}
#endif // CNC_H
