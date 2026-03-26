#ifndef UTILS_H
#define UTILS_H
#include <Nano.h>
#include <Port.h>
namespace Utils{
    template<Registers REG>
    struct RegistorAction : Base{
        static void assignByte(uint8_t&& byte){
            reference(REG)=byte;
        }
        static void setByte(uint8_t&& byte){
            reference(REG)|=byte;
        }
        static void resetByte(uint8_t&& byte){
            reference(REG)&=~byte;
        }
        static void toogleByte(uint8_t&& byte){
            reference(REG)^=byte;
        }
        static uint8_t reg(){
            return reference(REG);
        }
    };
    template<Registers REG>
    struct BitsAction : Base{
    };

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

        template< class PIN, uint16_t number, class P = void >
        struct pin_with_number{
            static constexpr bool value = false;
        };

        template< class PIN, uint16_t  number>
        struct pin_with_number<PIN, number, enable_if_t<(PIN::pinNumber == (1<<number))> >{
            static constexpr bool value = true;
        };

        template< class PIN, uint16_t  number>
        static constexpr bool pin_with_number_v = pin_with_number<PIN,number>::value;

        template<class T, class U>
        struct is_same {
            static constexpr bool value = false;
        };

        template<class T>
        struct is_same<T, T> {
            static constexpr bool value = true;
        };

        template<class T, class U>
        inline constexpr bool is_same_v = is_same<T, U>::value;

        template<uint8_t number, class ...U>
        struct any_pin_of{
            static constexpr bool value = ( (number == U::pinNumber) || ...);
        };

        template<uint8_t number, class ...U>
        inline constexpr bool any_pin_of_v = any_pin_of<number, U...>::value;

        template<uint8_t number, bool value>
        struct return_if{
        };

        template<uint8_t number>
        struct return_if<number,true>{
            static constexpr bool value = number;
        };
        template<uint8_t number, bool value>
        inline constexpr uint8_t return_if_v = return_if<number, value>::value;
    }
}
#endif // UTILS_H
