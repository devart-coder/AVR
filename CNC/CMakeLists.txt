cmake_minimum_required(VERSION 3.16)

project(CNC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CNC STATIC


  Point2D.h Point2D.cpp
  Place.h Place.cpp
  Tool.h Tool.cpp
  Point3D.h Point3D.cpp
  Movement.h
  PositionInterface.h

)

target_include_directories(CNC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CNC PUBLIC Nano Utils)
