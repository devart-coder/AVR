#ifndef BUFFER_H
#define BUFFER_H

#include <inttypes.h>
#include <UART.h>
template<class T=uint16_t, T CAP=64>
class Buffer
{
    char _string[CAP];
    T _begin = 0;
    T _end = 0;
public:
    Buffer(const char* s)
    {
        // _string = s;
        for(T i=0; s[i]!='\0'; ++i){
            _string[i]=s[i];
            ++_end;
        }
    }
    inline char at(const T index)const{
        if ((index>=_end)||(index<_begin))
            return -1;
        return _string[index];
    }
    inline T size() const{
        return _begin > _end ? _begin - _end : _end - _begin;
    }
    inline T begin(){
        return _begin;
    }
    inline T begin() const {
        return _begin;
    }
    inline T end(){
        return _end;
    }
    inline T end() const {
        return _end;
    }
    //Methods:
    inline T indexOf(char value) const {
        for(T i = 0; i!= _end; ++i)
            if(_string[i] == value)
                return i;
        return -1;
    }
    inline bool isEmpty(){
        for(T i = begin; i!= _end; ++i)
            if(_string[i]!=' ')
                return false;
        return true;
    }
    inline bool startWith(const char* s){
        for(T i=0; s[i]!='\0'; ++i)
            if(s[i]!=_string[i])
                return false;
        return true;
    }
    //trimm();
    //endWith();
    //find('');
    //replace('');
    //repaceIf('');
    //capacity();
    //split('');
    //set(number, char);
    //append();
    //operator+=;
    //
    inline char* get()const{
        return _string;
    }
};

#endif // BUFFER_H
