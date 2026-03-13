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
        using void_type = void;

        template<bool f, class T = void>
        struct enable_if{
        };

        template<class T>
        struct enable_if<true, T>{
            using type = T;
        };

        template<bool f, class T = void>
        using enable_if_t = typename enable_if<f,T>::type;

        //PinCheck
        template<class T , class = void>
        struct is_pin{
            static constexpr bool value = false;
        };

        template<class T>
        struct is_pin<T, void_type<decltype(T::pinNumber)>>{
            static constexpr bool value = true;
        };

        template<class T>
        using is_pin_v = typename is_pin<T>::value;

        template< class PIN, uint8_t number, class P = void >
        struct pin_with_number{
            static constexpr bool value = false;
        };

        template< class PIN, uint8_t  number>
        struct pin_with_number<PIN, number, enable_if_t<PIN::pinNumber == number, PIN> >{
            static constexpr bool value = true;
        };
    }
}
#endif // UTILS_H
