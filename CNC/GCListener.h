#ifndef GCLISTENER_H
#define GCLISTENER_H
#include <Tool.h>
#include <UART.h>
class GCListener{
        Tool tool;
    private:
        void listen(){
            while(1){
                System.in.receive();
            }
        }
        void CommandParse(const char* ){

        }
        void execute(){

        }
    public:
        GCListener(Tool t)
        :tool(t)
        { }
}

#endif // GCLISTENER_H
