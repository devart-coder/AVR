#ifndef BUFFER_H
#define BUFFER_H
#include <inttypes.h>
#include <Nano.h>
template<class T=uint16_t, T CAP=16>
class Buffer
{
    static constexpr T _capacity = CAP;
    T _begin;
    T _end;
    char _string[CAP];
public:
    Buffer(const char* s)
        :_begin(0), _end(0)
    {
        for(T i=0; s[i]!='\0'; ++i){
            _string[i]=s[i];
            ++_end;
        }
    }
     Buffer(const Buffer<T,CAP>& b)
        :_begin(0), _end(0)
    {
        Nano::PinD13::setMode(PinMode::OUTPUT);
        Nano::PinD13::setHigh();
    }
    inline char at(const T index)const{
        if ((index>=_end)||(index<_begin))
            return -1;
        return _string[index];
    }
    inline T size() const{
        return _begin > _end ? _begin - _end : _end - _begin;
    }
    inline T& begin(){
        return _begin;
    }
    inline T begin() const {
        return _begin;
    }
    inline T& end(){
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
    inline bool startWith(const char* s)const{
        if(_begin == _end)
            return false;

        T length = 0;
        for(;s[length]!='\0';++length);

        if( size() >= length){
            for(T i=0; i!=length; ++i){
                if(s[i]!=_string[i])
                    return false;
            }
        }else{
            for(T i=_begin; i!=_end; ++i){
                if(s[i]!=_string[i])
                    return false;
            }
        }
        return true;
    }
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
    inline bool set(T index, char newChar){
        auto oldChar = at(index);
        if(oldChar != -1){
            _string[index] = newChar;
            return true;
        }
        return false;
    }
    inline void append(const char* newString){
        for(T j=0; newString[j] != '\0'; ++j)
            append(newString[j]);
    }
    inline void append(char newChar){
        _string[_end++]=newChar;
        _end %= _capacity;
    }
    inline void flush(){
        _begin = 0;
        _end = 0;
    }
};

#endif // BUFFER_H
