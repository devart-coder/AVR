#define F_CPU 16000000UL
#include <Tool.h>
// #include <Point3D.h>
#include <UART.h>
#include <Delay.h>
int main()
{
    auto tool = Tool<MicroStep::_default,uint8_t>();
    System.out.println("Start");
        System.out.print("X: ");
        System.out.print(tool.position().x().get());
        System.out.print(" Y: ");
        System.out.print(tool.position().y().get());
        System.out.print(" Z: ");
        System.out.println(tool.position().z().get());
    for(uint8_t i=0;i!=10;++i){
        System.out.println("New Positions: ");

        System.out.print("X: ");
        System.out.print(tool.position().x().inc());
        System.out.print(" Y: ");
        System.out.print(tool.position().y().dec());
        System.out.print(" Z: ");
        System.out.println(tool.position().z().get());

        delayMs(1000);

    }
    return 0;
}
