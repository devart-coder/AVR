cmake_minimum_required(VERSION 3.16)

project(Utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Utils STATIC
  conversion.cpp
  conversion.h
)

# target_include_directories(Utils PUBLIC .)
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(Utils PRIVATE Nano)


