#ifndef BUS_H
#define BUS_H
#include <inttypes.h>
#include <Base.h>
#include <Utils.h>
#include <GetType.h>
#include <Pin.h>

template<class ...T>
class Bus : Base{
    public:
        template<uint8_t n>
        using get = typename GetType<n, T...>::type;

    private://Functions
        template<class HEAD, class... TAIL>
        struct FirstType{
            using type = HEAD;
        };
        template<class P>
        static inline void writeBit(bool bit){
            bit == true ? P::setHigh() : P::setLow();
        }
        template<class P>
        static inline void setDirectionBit(bool bit){
            bit == true ? P::setMode(PinMode::OUTPUT) : P::setMode(PinMode::INPUT);
        }

    private://Types
        using FirstPin = typename GetType<1, T...>::type;
        using FirstPort = typename FirstPin::portType;

    private://Values
        static constexpr uint8_t  pinPositions = ( T::pinNumber | ... );
        static constexpr bool  singlePort = ( Utils::Templates::is_same_v<typename T::portType , FirstPort>  && ... );
    public:
        static inline void write(uint8_t byte){
                uint8_t index = 0 ;
            if constexpr (singlePort){
                uint8_t portBits = 0;
                portBits|= ( (((byte >> index++)&1) ? T::pinNumber : 0) |...);
                FirstPort::write( (~(pinPositions)&FirstPort::read()) | portBits );
            }else{
                (writeBit<T>( ((byte>>index++)&1) ), ...);
            }
        }
        static inline void writeMask(uint8_t byte){
                uint8_t index = 0 ;
            if constexpr (singlePort){
                uint8_t portBits = 0;
                portBits|= ( (((byte >> index++)&1) ? T::pinNumber : 0) |...);
                FirstPort::writeMask( (~(pinPositions)&FirstPort::read()) | portBits );
            }else{
                (writeBit<T>( ((byte>>index++)&1) ), ...);
            }
        }
        static inline void setDirection(uint8_t mask){
            uint8_t index=0;
            if constexpr (singlePort){
                uint8_t portBits = 0;
                portBits|= ( (((mask >> index++)&1) ? T::pinNumber : 0) |...);
                FirstPort::setModeMask( ((~pinPositions & reference(FirstPort::ddr)) | portBits) );
            }else{
                (setDirectionBit<T>(((mask>>index++)&0x01)), ...);
            }
        }
};
#endif // BUS_H
