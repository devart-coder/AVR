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
    //Examle: 4,5,6
    static constexpr uint8_t  mask = ( (1<<T::pinNumber) | ... );
    static constexpr uint8_t  size = sizeof...(T);
    public:
    static inline void write(uint8_t byte){
        uint8_t portBits = 0;
        uint8_t i=0;
        // ( portBits|= ( ((byte >> i++)&1) |...));
    }
    //read
};
#endif // BUS_H
