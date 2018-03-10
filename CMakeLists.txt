cmake_minimum_required(VERSION 3.8)
project(Spheralizer)

set(CMAKE_CXX_STANDARD 14)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_PREFIX}/cmake")

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Link against libraries
target_link_libraries(<yourProjectName> ${WIRINGPI_LIBRARIES})
target_link_libraries(<yourProjectName> ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES main.cpp
        utils.cpp
        utils.h)
add_executable(Spheralizer ${SOURCE_FILES})