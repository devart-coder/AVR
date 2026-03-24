#ifndef POINT2D_H
#define POINT2D_H
#include <inttypes.h>
template< class T = uint32_t>
class Point2D
{
    private:
        T XPosition;
        T YPosition;
    public:
        Point2D( T x, T y);
        Point2D( const Point2D<T>& point);
        Point2D( const Point2D<T>&& point);

        void setX(const T &newXPosition)
        {
            XPosition = newXPosition;
        }
        T x() const
        {
            return XPosition;
        }
        void setY(const T &newYPosition)
        {
            YPosition = newYPosition;
        }
        T y() const
        {
            return YPosition;
        }
        //incX(T value);
        //decX(T value);
        //dx()

        //incY(T value);
        //decY(T value);
};

#endif // POINT2D_H
