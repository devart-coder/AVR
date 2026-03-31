#ifndef POINT3D_H
#define POINT3D_H
#include <Point2D.h>
template<class T = uint32_t>
class Point3D : public Point2D<T>
{
    using Position = PositionInterface<T>;
    Position z_pos;
public:
    Position& z(){
        return z_pos;
    }
    Position z() const {
        return z_pos;
    }
    Point3D(T x=0, T y=0, T z=0)
        :Point2D<T>(x,y),z_pos(Position(z))
    { }
    Point3D(const Point2D<T>& point2D, T z)
        :Point2D<T>(point2D), z_pos(Position(z))
    { }
    Point3D(const Point3D<T>& point3D)
        :Point3D(point3D.x().get(), point3D.y().get(), point3D.z().get())
    { }
};

#endif // POINT3D_H
