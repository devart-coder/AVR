#ifndef UTILS_H
#define UTILS_H
#include <Nano.h>
#include <Port.h>
namespace Utils{
    namespace Conversions {
        unsigned int digits(unsigned int number){
            int i=0;
            for(; number!=0; ++i)
                number/=10;
            return i;
        }
        void toString(unsigned int number, char* buffer){
            auto d = digits(number);
            buffer[d--]='\0';
            for(; number!=0; --d){
                buffer[d]=number%10+'0';
                number/=10;
            }
        }
    }
    namespace Templates {

        template <typename...>
        using voidType = void;

        template<bool f, class T = void>
        struct enableIf{
        };

        template<class T>
        struct enableIf<true, T>{
            using type = T;
        };

        template<bool f, class T = void>
        using enableIfType = typename enableIf<f,T>::type;

        //PinCheck
        template<class T , class = void>
        struct isPin{
            static constexpr bool value = false;
        };

        template<class T>
        struct isPin<T, voidType<decltype(T::pinNumber)>>{
            static constexpr bool value = true;
        };
        //pinWithNumber<5>::value
        template< class PIN, uint8_t number, class P = void >
        struct pinWithNumber{
            static constexpr bool value = false;
        };

        template< class PIN, uint8_t  number>
        struct pinWithNumber<PIN, number, enableIfType<PIN::pinNumber == number, PIN> >{
            static constexpr bool value = true;
        };
    }
}
#endif // UTILS_H
