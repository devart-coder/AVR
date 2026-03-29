#ifndef TOOL_H
#define TOOL_H
#include <Place.h>
#include <Point3D.h>

template <MicroStep SIZE = _default, class T = uint32_t>
class Tool{
        static constexpr uint16_t size = static_cast<uint16_t>(SIZE);
        Place<SIZE,T> _place = Place<SIZE,T>();
        Point3D<T> point = Point3D<T>();
        T Zpos;
    public:
        explicit Tool(T x=0, T y=0, T z=0)
        {

        }
        explicit Tool(const Point2D<T>& point2D, T z=0)
        {

        }
        explicit Tool(const Point3D<T>& point3D)
        {

        }
        Place<SIZE,T>& place(){
            return _place;
        }
        void left(uint32_t value)
        {
            Movement::x.left();
            Movement::x.steps(value*size);
        }
        void right(uint32_t value){
            Movement::x.right();
            Movement::x.steps(value*size);
        }
        void up(T value){
            Movement::z.up();
            Movement::z.steps(value*size);
        }
        void down(T value){
            Movement::z.down();
            Movement::z.steps(value*size);
        }
        void z() const{
            return Zpos;
        }
        void move(const Point2D<T>& p){

        }
        void move(T x, T y){

        }
        //Gcommand();
};

#endif // TOOL_H
