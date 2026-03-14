#ifndef BUS_H
#define BUS_H
#include <inttypes.h>
#include <Base.h>
#include <Utils.h>
/*


*/
using namespace Utils::Templates;
template<class ...T>
class Bus : Base{
    static constexpr uint8_t  bitNumber = ( T::pinNumber | ... );

    template<class HEAD, class... TAIL>
    struct FirstType{
        using type = HEAD;
    };
    using FirstPin = typename FirstType<T...>::type;
    using FirstPort = typename FirstPin::portType;
    static constexpr bool  singlePort = ( is_same_v<typename T::portType , FirstPort>  && ... );

    template<class P>
    static inline void writeBit(bool bit){
        bit == true ? P::setHigh() : P::setLow();
    }
    public:
    static inline void write(uint8_t byte){
        if constexpr (singlePort){
            uint8_t portBits = 0;
            uint8_t index=0;
            ( portBits|= ( (((byte >> index++)&1) ? T::pinNumber : 0) |...) );
            reference(FirstPort::port)|= ((~bitNumber)|portBits);
        }else{
            uint8_t index = 0 ;
            (writeBit<T>(((byte>>index++)&0x01)), ...);
        }
    }
    static inline void setBusMode(){

    }
    static inline void setBusModeMask(uint8_t mask){
        reference(Registers::R_DDRD)|= ((~bitNumber)|mask);
    }
};
#endif // BUS_H
