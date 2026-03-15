#include "Callable.h"

void Callable::setCallback(HandleType f){
    callback=f;
}

void Callable::handle(){
    callback();
}
