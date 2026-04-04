#ifndef STRING_H
#define STRING_H

#define F_CPU 16000000UL
#include <inttypes.h>
#include <UART.h>
template<class T=uint8_t>
class Buffer
{
    char* _string=nullptr;
public:
    Buffer(char* s)
    {
        _string = s;
    }
        // : _capacity(cap)
    // {
        // char c[cap];
        // _string = &c;
    // }
    // T capacity(){
        // return _capacity;
    // }
    inline char* get()const{
        return _string;
    }
};

#endif // STRING_H
