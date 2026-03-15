cmake_minimum_required(VERSION 3.16)

project(Utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Utils STATIC
  Utils.cpp
  Utils.h
  Pin.h
  Port.h
  Bus.h
  Callable.h
  Base.h
  Base.cpp
  Callable.cpp
  Pin.cpp
  GetType.h
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Utils PUBLIC Nano)
