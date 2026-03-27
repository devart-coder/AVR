#ifndef POINT3D_H
#define POINT3D_H
#include <Point2D.h>
template<class T = uint32_t>
class Point3D : public Point2D<T>
{
    T zPosition;
public:
    Point3D(T x=0, T y=0, T z=0);
    Point3D(const Point2D<T>& point2D, T z);
    Point3D(const Point3D<T>& point3D);
    Point3D(const Point3D&& point3D);
};

#endif // POINT3D_H
