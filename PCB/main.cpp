#define F_CPU 16000000UL
#include <Nano.h>
#include <Tool.h>
#include <Delay.h>
#include <String.h>
using namespace Nano;
int main()
{
    auto tool = Tool();
    while(1){
        // auto cap = System.in.buffer().capacity();
        // auto l = System.in.buffer().length();
        // auto b = System.in.buffer().get();
        // System.out.print("Cap: ");
        // System.out.print(cap);
        // System.out.print(" Len: ");
        // System.out.print(l);
        // System.out.print(" ");
        // System.out.println(b, l);
        // if(b == "Hello"){
        //     PinD13::isHigh();
        // }
        // System.out.println(s2.get());
        // {
            // s2 = String("Hello");
        // }
        // System.out.print(s.get());
        // System.out.println(s2.get());
        char b[] = {'1','2','3','4'};
        auto b1 = Buffer(b);
        auto b2 = Buffer("Hello World!");
        // System.out.print("B1");
        System.out.print(b2.get(),3);
        System.out.println(b1.get(),3);

        delayMs(1000);
    }
    return 0;
}
