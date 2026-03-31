#define F_CPU 16000000UL
#include <Tool.h>
#include <Delay.h>
int main()
{
    auto tool = Tool<MicroStep::_default,int32_t>();
    System.out.println("Start");
    tool.print();
    tool.down(50);
    for(uint32_t i=1;i!=6;++i){
        tool.shift(i*200,(i%2) ? 200 : 0);
        tool.print();
    }
    tool.up(50);
    for(uint32_t i=4;i!=-1; --i){
        tool.shift(i*200, (i%2) ? 200 : 0);
        tool.print();
    }
        System.out.println("Stop");
    return 0;
}
