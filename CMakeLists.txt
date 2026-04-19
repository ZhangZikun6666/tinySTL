cmake_minimum_required(VERSION 3.29)
project(tinySTL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SOURCES "*.cpp")
add_executable(tinySTL ${SOURCES}
        vector.h
        constuct.h)