#ifndef PLACE_H
#define PLACE_H
#include <Point2D.h>
//rightTo();
//leftTo();
//upTo();
//downTo();
template<class T=uint32_t>
class Place
{
        Point2D<T> point;
    public:
        explicit Place(T x=0, T y=0);
        explicit Place(const Point2D<T>& point);
        void moveTo(const Point2D<T>& newPoint);
        void moveTo(T&& x2, T&& y2);
};

#endif // PLACE_H
