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
    static constexpr uint8_t  pinPositions = ( T::pinNumber | ... );
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
    template<class P>
    static inline void setDirectionBit(bool bit){
        bit == true ? P::setMode(P::Direction::OUTPUT) : P::setMode(P::Direction::INPUT);
    }
    public:
    static inline void write(uint8_t byte){
        if constexpr (singlePort){
            uint8_t portBits = 0;
            uint8_t index=0;
            ( portBits|= ( (((byte >> index++)&1) ? T::pinNumber : 0) |...) );
            FirstPort::write( ((~pinPositions & FirstPort::read())| portBits) );
        }else{
            uint8_t index = 0 ;
            (writeBit<T>(((byte>>index++)&0x01)), ...);
        }
    }
    static inline void setBusDirectionMask(uint8_t mask){
        if constexpr (singlePort){
            uint8_t portBits = 0;
            uint8_t index=0;
            ( portBits|= ( (((mask >> index++)&1) ? T::pinNumber : 0) |...) );
            FirstPort::setDirectionMask( ((~pinPositions & reference(FirstPort::ddr)) | portBits) );
        }else{
            uint8_t index = 0 ;
            (setDirectionBit<T>(((mask>>index++)&0x01)), ...);
        }
    }
};
#endif // BUS_H
