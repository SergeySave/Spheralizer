cmake_minimum_required(VERSION 3.7.2)
project(Spheralizer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
        utils.cpp
        utils.h
        drawAPI.cpp
        drawAPI.h)

add_executable(Spheralizer ${SOURCE_FILES})