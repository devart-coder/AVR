#include <Nano.h>
// #include <Delay.h>
#include <PWM.h>
using namespace Nano;
int main()
{
    PinD9::setMode(PinMode::OUTPUT);
        // pinMode(9, OUTPUT);

        // 1. Сброс настроек
        PWMD9::setDefaultSettings();
        ICR1 = 6000;

        // 3. Предделитель 8
        // TCCR1B |= (1 << CS11);

        // 4. Установка периода (например, 20кГц для тихих моторов)
        // 16МГц / (1 * 20000) - 1 = 799. Предделитель 1 (CS10)
        // ICR1 = 799;
        // TCCR1B &= ~(1 << CS11); TCCR1B |= (1 << CS10);

        // 5. Начальное заполнение 50%
        PWMD9::setDirtyNumber(6000/2);
        // OCR1AL = 6000/2;



    while(1){
        // for(uint8_t i =0; i!=100; ++i){
        //     PWMD6::setDirtyNumber(i);
        //     delayMs(3);
        // }
        // for(uint8_t i = 100; i!=0; --i){
        //     PWMD6::setDirtyNumber(i);
        //     delayMs(3);
        // }
    }
    return 0;
}
