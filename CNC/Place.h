#ifndef PLACE_H
#define PLACE_H
#include <Point2D.h>
#include <Movement.h>
//Transmission:
//1 == 4 mm
//Engine:
//1 == 200 steps
//EngineDriver
//1 == 1/16

// 4mm == 200 steps * 16 == 3200 steps
// 1mm == 1000 mkm == 800 steps
// 0.1mm == 100 mkm == 80 steps (<-) default
// 0.01mm == 10mkm == 8 steps

// 5mm == 200 steps * 16 == 3200 steps
// 1mm == 1000 mkm == 640 steps
// 0.1mm == 100 mkm == 64 steps (<-) default
// 0.01mm == 10mkm == 8 steps
enum Size {
    _1mm_ = 800,
    _01mm_ = 80,
    _001mm_ = 8,
    _default = _01mm_
};
template<Size SIZE, class T=uint32_t>
class Place
{
    Point2D<T> point;
    uint16_t size = static_cast<uint16_t>(SIZE);
    static constexpr uint32_t FULL_TURN = 3200;
    public:
        explicit Place(T x=0, T y=0)
            : point(x,y)
        { }
        explicit Place(const Point2D<T>& p)
            : point(p)
        { }
        void up( uint32_t value)
        {
            Movement::y.up();
            Movement::y.steps(value * size);
        }
        void down(uint32_t value)
        {
            Movement::y.down();
            Movement::y.steps(value*size);
        }

};
#endif // PLACE_H
