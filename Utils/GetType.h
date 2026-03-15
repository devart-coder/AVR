#ifndef GETTYPE_H
#define GETTYPE_H
#include <inttypes.h>

template<uint8_t index, class HEAD, class ...TAIL>
struct GetType{
    using type = typename GetType<index-1,TAIL...>::type;
};

template<class HEAD, class ...TAIL>
struct GetType<0, HEAD, TAIL...>{
    using type = HEAD;
};
#endif // GETTYPE_H
