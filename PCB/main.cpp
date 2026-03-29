#define F_CPU 16000000UL
#include <Tool.h>
int main()
{
    auto tool = Tool();
    while(1){
        tool.place.up(500);
        // place.up(10);//-50.0mm
        delayMs(1000);//wait

        tool.place.down(500);//+50.0mm
        delayMs(1000);//wait

        tool.right(500);//+50.0mm
        delayMs(1000);//wait

        tool.left(500);//-50.0mm
        delayMs(1000);//wait

        tool.up(500);
        delayMs(1000);//wait

        tool.down(500);
        delayMs(1000);//wait
    }
    return 0;
}
