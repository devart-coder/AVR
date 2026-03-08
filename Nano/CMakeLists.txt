cmake_minimum_required(VERSION 3.16)

project(Nano LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(Nano STATIC
    Atmega328p.h
    Nano.h
    Pin.h
    Pin.cpp
    Port.h
    Bus.h

    Delay.h
    PWD.h
    Timer0.h Timer0.cpp
    Base.h Base.cpp
    UART.h

)
target_include_directories(Nano PUBLIC .)
