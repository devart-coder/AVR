#ifndef BUFFER_H
#define BUFFER_H

#include <inttypes.h>
#include <UART.h>
template<class T=uint16_t, T CAP=32>
class Buffer
{
    char _string[CAP];
    static constexpr T _capacity = CAP;
    T _begin = 0;
    T _end = 0;
public:
    Buffer(const char* s)
    {
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
        return _begin == _end ? true : false;
    }
    inline bool startWith(const char* s){
        for(T i=0; s[i]!='\0'; ++i)
            if(s[i]!=_string[i])
                return false;
        return true;
    }
    //trimm();
    //endWith();
    inline bool replace(char oldChar, char newChar){
        return replaceIf([&oldChar](char c){return c == oldChar;}, newChar);
    }
    template<class Predicate>
    inline bool replaceIf( Predicate func, char newChar){//O(N)
        bool replacedFlag = false;
        for(T i = _begin; i!=_end; ++i){
            if(func(_string[i])){
                _string[i] = newChar;
                replacedFlag = true;
            }
        }
        return replacedFlag;
    }
    inline T capacity(){
        return _capacity;
    }
    //split('');
    inline bool set(T index, char newChar){
        auto oldChar = at(index);
        if(oldChar != -1){
            _string[index] = newChar;
            return true;
        }
        return false;
    }
    inline bool append(const char* newString){

    }
};

#endif // BUFFER_H
