#include "Base.h"


volatile uint8_t &Base::reference(uint16_t &&addr){
    return *reinterpret_cast<volatile uint8_t*>(addr);
}
