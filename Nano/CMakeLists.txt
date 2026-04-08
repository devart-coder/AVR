cmake_minimum_required(VERSION 3.16)

project(Nano LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(Nano STATIC
    Atmega328p.h
    Nano.h
    Delay.h
    PWM.h
    Timer.h
    UART.h
    ExternalInterrupt.h
    SoftPWM.h

)
target_include_directories(Nano PUBLIC .)
target_link_libraries(Nano PUBLIC Utils)
