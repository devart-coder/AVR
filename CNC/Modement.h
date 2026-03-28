#ifndef MODEMENT_H
#define MODEMENT_H
#include <Nano.h>

class Movement{
    class XAxis{
            using XDir  = Nano::PinD2;
            using XStep = Nano::PinD5;
        public:
            static inline right(){}
            static inline left(){}
            static inline step(){}
    };
    class YAxis{
            using YDir  = Nano::PinD3;
            using YStep = Nano::PinD6;
        public:
            static inline forward(){}
            static inline behavor(){}
            static inline step(){}
    };
    class ZAxis{
            using ZDir  = Nano::PinD4;
            using ZStep = Nano::PinD7;
        public:
            static inline up(){}
            static inline down(){}
            static inline step(){}
    };
    public:


}


#endif // MODEMENT_H
