#ifndef GCLISTENER_H
#define GCLISTENER_H
#include <Tool.h>
#include <UART.h>
#include <Nano.h>
#include <Delay.h>
class GCListener{
    Tool<MicroStep::_default> tool;
    private:
    template <class T, T CAP>
        void CommandParse(Buffer<T,CAP>& buffer ){
                uart.out.print("Buffer: ");
                uart.out.println(buffer);
            if(buffer.startWith("G00"))
                Nano::PinD13::setHigh();
            if(buffer.startWith("G01"))
                Nano::PinD13::setLow();
        }
        void execute(const char* gc){
        }
    public:
        GCListener(const Tool<MicroStep::_default>& t)
        :tool(t)
        {
            Nano::PinD13::setMode(PinMode::OUTPUT);
        }
        void listen(){
            while(1){
                while(uart.in.buffer().size()==0)
                    delayUs(100);

                CommandParse(uart.in.buffer());
                uart.in.buffer().flush();
            }
        }
};

#endif // GCLISTENER_H
