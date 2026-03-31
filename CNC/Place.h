#ifndef PLACE_H
#define PLACE_H
#include <Point3D.h>
#include <Movement.h>
#include <Utils.h>
//Transmission:
//1 == 4 mm

//Engine:
//1 == 200 steps

//EngineDriver
//1 == 1/16

// 4mm     == 200 steps * 16 == 3200 steps
// 1mm     == 1000 mkm == 800 steps
// 0.1mm   == 100 mkm == 80 steps (<-) default
// 0.01mm  == 10mkm ==  8 steps
//0.005mm  ==  5mkm ==  4 steps
//0.0025mm == 2.5mkm == 2 steps
enum MicroStep {
    _1_mm_   = 800,
    _0_1mm_  = 80,
    _0_01mm_ = 8,
    _5mkm_  = 4,
    _default = _0_01mm_
};
using Utils::Templates::enable_if_t;
using Utils::Templates::is_numeric_v;

template<MicroStep SIZE, class T , class U = enable_if_t<(is_numeric_v<T>)>>
class Place
{
    using Position = PositionInterface<T>;
    Position& y_pos = nullptr;
    uint16_t size = static_cast<uint16_t>(SIZE);

    public:
        Place(Position& y)
            :y_pos(y){
        }
        T up(T value=1)
        {
            Movement::y.up();
            Movement::y.steps(value * size);
            return y_pos.inc(value);
        }
        T down(T value=1)
        {
            Movement::y.down();
            Movement::y.steps(value*size);
            return y_pos.dec(value);
        }

};
#endif // PLACE_H
