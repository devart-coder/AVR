cmake_minimum_required(VERSION 3.16)

project(Nano LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(Nano STATIC
    Atmega328p.h
    Nano.h
    Delay.h
    PWD.h
    Timer0.h Timer0.cpp
    UART.h
    ExternalInterrupt.h
)
target_include_directories(Nano PUBLIC .)
target_link_libraries(Nano PUBLIC Utils)
