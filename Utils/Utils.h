#ifndef UTILS_H
#define UTILS_H

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
}
#endif // UTILS_H
