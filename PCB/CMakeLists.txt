cmake_minimum_required(VERSION 3.16)

project(PCB LANGUAGES CXX)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MCU atmega328p)
set(F_CPU 16000000UL)
# Важные флаги для AVR
add_compile_options(
    -fno-exceptions       # На AVR нет поддержки исключений (сэкономят кучу памяти)
    -fno-rtti             # Отключаем Run-Time Type Information
    -ffunction-sections   # Позволяет линковщику удалять неиспользуемый код
    -fdata-sections
    -mmcu=${MCU}
    -Os
    -Wall
)
add_definitions("-DF_CPU=${F_CPU}")
add_link_options(-mmcu=${MCU})
# Флаги линковки для удаления "мёртвого" кода шаблонов
add_link_options(-Wl,--gc-sections)

add_executable(PCB main.cpp)
target_link_libraries(PCB PUBLIC Nano Utils CNC)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND avr-objcopy -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex)

add_custom_target(upload
    COMMAND avrdude -c arduino -p m328p -P /dev/ttyUSB* -b 115200 -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}
    COMMENT "Uploading to Arduino Nano..."
)
add_custom_target(size
    COMMAND avr-size ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}
)
