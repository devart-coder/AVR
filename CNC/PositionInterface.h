#ifndef POSITIONINTERFACE_H
#define POSITIONINTERFACE_H
#include <inttypes.h>

template<class T = uint32_t>
class PositionInterface{
        T p;
    public:
        PositionInterface()
            :p(0)
        {}
        PositionInterface(T value)
            :p(value)
        {}
        void set(T value){
            p=value;
        }
        T inc(T value = 1){
            p+=value;
            return p;
        }
        T dec(T value = 1){
            p-=value;
            return p;
        }
        T get() const{
            return p;
        }
};
#endif // POSITIONINTERFACE_H
