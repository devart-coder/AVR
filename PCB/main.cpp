#define F_CPU 16000000UL
// #include <Tool.h>
#include <Point3D.h>
#include <UART.h>
#include <Delay.h>
int main()
{
    UART::Setting::defaultSettings();
    // auto tool = Tool();
    Point3D point = Point3D<unsigned int>(0,2,3);
    System.out.println("Start");
        System.out.print("X: ");
        System.out.print(point.x().get());
        System.out.print(" Y: ");
        System.out.print(point.y().get());
        System.out.print(" Z: ");
        System.out.println(point.z().get());
    for(uint32_t i=0;i!=10;++i){
        System.out.println("New Positions: ");

        System.out.print("X: ");
        System.out.print(point.x().inc());
        System.out.print(" Y: ");
        System.out.print(point.y().dec());
        System.out.print(" Z: ");
        System.out.println(point.z().get());

        delayMs(1000);

    }
    return 0;
}
