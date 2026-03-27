#ifndef TOOL_H
#define TOOL_H
#include <Place.h>
#include <Point3D.h>
//Transmission:
//1 == 4 mm

//Engine:
//1 == 200 steps

//EngineDriver
//1 == 1/16

// 4mm == 200 steps * 16 == 3200 steps
// 1mm == 1000 mkm == 800 steps
// 0.1mm == 100 mkm == 80 steps (<-)
// 0.01mm == 10mkm == 8 steps

//Pattern::Singletone
template <class T = uint32_t>
class Tool{
    static constexpr uint16_t FULL_TURN_STEPS = 3200;
    T Zposition;
    Place<T> place = Place<T>();
    uint16_t speed = 1;

    //Gcommand();

    public:
    explicit Tool(T x=0, T y=0, T z=0);
    explicit Tool(const Point2D<T>& point2D, T z=0);
    explicit Tool(const Point3D<T>& point3D);
        void zUp(T&& );
        void zDown();
        void z()const;
};

#endif // TOOL_H
