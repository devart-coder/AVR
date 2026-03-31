#ifndef POINT2D_H
#define POINT2D_H
#include <inttypes.h>
#include <PositionInterface.h>
template< class T = uint32_t>
class Point2D
{
    private:
    using Position = PositionInterface<T>;
        Position x_pos;
        Position y_pos;
    public:

        Point2D( T x, T y)
            : x_pos(Position(x)), y_pos(Position(y))
        {}
        Point2D(const Point2D<T>& point)
            : x_pos(Position(point.x())), y_pos(Position(point.y()))
        {}
        Position& x(){
            return x_pos;
        }
        Position x() const {
            return x_pos;
        }
        Position& y(){
            return y_pos;
        }
        Position y() const{
            return y_pos;
        }
};

#endif // POINT2D_H
