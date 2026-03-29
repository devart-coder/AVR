#ifndef POINT2D_H
#define POINT2D_H
#include <inttypes.h>
template< class T = uint32_t>
class Point2D
{
    private:
        T x_pos;
        T y_pos;
    public:
        Point2D( T x, T y)
            : x_pos(x), y_pos(y)
        {}
        Point2D(const Point2D<T>& point)
            : x_pos(point.x()), y_pos(point.y())
        {}

        void setX(const T &newXPosition)
        {
            x_pos = newXPosition;
        }
        T x() const
        {
            return x_pos;
        }
        void setY(const T &newYPosition)
        {
            y_pos = newYPosition;
        }
        T y() const
        {
            return y_pos;
        }
        //xInc(T value);
        //decX(T value);

        //incY(T value);
        //decY(T value);

        //+=x2,y2;
        //+=Point2D(x2,y2);


        //-=x2,y2;
        //-=Point2D(x2,y2);
};

#endif // POINT2D_H
