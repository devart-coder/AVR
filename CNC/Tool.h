#ifndef TOOL_H
#define TOOL_H
#include <Place.h>
#include <Point3D.h>
#include <Utils.h>
#include <UART.h>
#include <stdlib.h>
using Utils::Templates::is_numeric_v;
using Utils::Templates::enable_if_t;
template <MicroStep MS = _default, class T = int32_t, class U = enable_if_t<(is_numeric_v<T>)>>
class Tool{
        static constexpr uint16_t microStep = static_cast<uint16_t>(MS);
        Place<MS,T> _place;
        Point3D<T> point;
        using Graver = Nano::PinD13;
    private://Methods
        void move(T x, T y){
            T dx = x - point.x().get();
            T dy = y - point.y().get();
            if(dx==1)
                right();
            else if(dx == -1)
                left();
            if(dy==1)
                place().up();
            else if(dy == -1)
                place().down();
        }
    public:
        explicit Tool(T x=0, T y=0, T z=0)
            :point(Point3D(x,y,z)), _place(Place<MS,T>(point.y()))
        {
            Graver::setMode(PinMode::OUTPUT);
        }
        explicit Tool(const Point2D<T>& point2D, T z=0)
            :Tool(point2D.x().get(), point2D.y().get(), z)
        { }
        explicit Tool(const Point3D<T>& point3D)
            : Tool(point3D.x().get(), point3D.y().get(), point3D.z().get())
        { }
        Place<MS,T>& place(){
            return _place;
        }
        void left(T value=1)
        {
            Movement::x.left();
            Movement::x.steps(value*microStep);
            point.x().dec(value);
        }
        void right(T value=1){
            Movement::x.right();
            Movement::x.steps(value*microStep);
            point.x().inc(value);
        }
        void up(T value=1){
            Movement::z.up();
            Movement::z.steps(value*microStep);
            point.z().inc(value);
        }
        void down(T value=1){
            Movement::z.down();
            Movement::z.steps(value*microStep);
            point.z().dec(value);
        }
        Point3D<T>& position(){
            return point;
        }
        Point3D<T> position() const {
            return point;
        }
        void drawLine(const Point2D<T>& p){

        }
        void shift(T x_1, T y_1){//bezenhamAlgorithm
            auto x_0 = point.x().get();
            auto y_0 = point.y().get();

            T dx = abs(x_1 - x_0);
            T dy = abs(y_1 - y_0);

            T dirX = ((x_1 - x_0) > 0) ? 1 : ((x_1 - x_0) == 0) ? 0 : -1;
            T dirY = ((y_1 - y_0) > 0) ? 1 : ((y_1 - y_0) == 0) ? 0 : -1;

            T error = 0;
            if(dx >= dy){
                T derror = dy;
                for(T x = x_0, y = y_0; x != x_1+dirX; x+=dirX){
                    move(x,y);
                    error+=derror;
                    if(error>=dx){
                        y+=dirY;
                        error-=dx;
                    }
                }
            }else{
                T derror = dx;
                for(T x = x_0, y = y_0; y != y_1+dirY; y+=dirY){
                    move(x,y);
                    error+=derror;
                    if(error>=dy){
                        x+=dirX;
                        error-=dy;
                    }
                }
            }
        }
        void shift(T x_1, T y_1, T z_1 ){
            T dz = z_1 - point.z().get();
            if(dz>0)
                up(z_1);
            else if(dz<0)
                down(z_1);
            shift(x_1, y_1);
        }
        //Gcommand();
        void print(){

            System.out.print("X: ");
            if constexpr (microStep == MicroStep::_0_01mm_){
                auto x = point.x().get();
                System.out.print(x/100);
                System.out.print(".");
                System.out.print(x%100);
            }
            System.out.print(" Y: ");
            if constexpr (microStep == MicroStep::_0_01mm_){
                auto y = point.y().get();
                System.out.print(y/100);
                System.out.print(".");
                System.out.print(y%100);
            }
            System.out.print(" Z: ");
            if constexpr (microStep == MicroStep::_0_01mm_){
                auto z = point.z().get();
                System.out.print(z/100);
                System.out.print(".");
                System.out.println(z%100);
            }
        }
        void home(){
            shift(0,0,0);
        }
        void enable(){
            Graver::setHigh();
        }
        void disable(){
            Graver::setLow();
        }

        void drawLine(T x_0, T y_0, T x_1, T y_1){
            // shift();
        }
        void drawLine(const Point2D<T>& begin, const Point2D<T>& end){
            drawLine(begin.x().get(), begin.y().get(), end.x().get(), end.y().get());
        }
        void drawCircle(T x_0, T y_0, T radius){
            int x = 0;
            int y = 0;
            int err = 2 - 2 * radius; // Начальная ошибка

            do {
                // 1. Команда шпинделю: ехать в точку (x0 + x, y0 + y)
                shift(x_0 + x, y_0 + y);

                int e2 = err;
                if (e2 <= y)
                    err += (++y) * 2 + 1;
                if (e2 > x || err > y)
                    err += (++x) * 2 + 1;
            } while (x <= 0); // Проход половины или четверти (настраивается условием)
        }
        void drawCircle(const Point2D<T>& center, T radius){
            drawCircle(center.x().get(), center.y.get(), radius);
        }

};

#endif // TOOL_H
