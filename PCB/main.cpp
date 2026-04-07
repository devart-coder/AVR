#define F_CPU 16000000UL
#include <Nano.h>
#include <UART.h>
#include <GCListener.h>
using namespace Nano;
int main()
{
    UART<64>::Setting::setBaudRate(BaudRate::_115200);
    GCListener listener = GCListener(Tool<MicroStep::_default>());
    listener.listen();
    return 0;
}
