#define F_CPU 16000000UL
#include <Tool.h>
#include <Delay.h>
int main()
{
    auto tool = Tool();
    while(1){
        System.out.print(tool.buffer, tool.head, tool.tail);
        delayMs(3000);
    }
    return 0;
}
