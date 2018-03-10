cmake_minimum_required(VERSION 3.8)
project(Spheralizer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
        utils.cpp
        utils.h)
add_executable(Spheralizer ${SOURCE_FILES})