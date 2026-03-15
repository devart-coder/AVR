#ifndef CALLABLE_H
#define CALLABLE_H
template<class T>
class Callable
{
    protected:
        using HandleType = T;
        static inline HandleType callback = nullptr;
    public:
        static void setCallback(HandleType f ){
            callback=f;
        }
        static void handle(){
            callback();
        }
};

#endif // CALLABLE_H
