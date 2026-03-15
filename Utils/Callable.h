#ifndef CALLABLE_H
#define CALLABLE_H

class Callable
{
        using HandleType = void (*)();
        static inline HandleType callback = nullptr;
    public:
        static void setCallback(HandleType f );
        static void handle();
};

#endif // CALLABLE_H
