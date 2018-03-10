cmake_minimum_required(VERSION 3.7.2)
project(Spheralizer)

set(CMAKE_CXX_STANDARD 14)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if (NOT WIN32 AND NOT APPLE AND UNIX)
    # Locate libraries and headers
    find_package(WiringPi REQUIRED)
    find_package(Threads REQUIRED)

    # Include headers
    include_directories(${WIRINGPI_INCLUDE_DIRS})
else ()
    include_directories("wiringPi")
endif ()

set(SOURCE_FILES main.cpp

        )

add_executable(Spheralizer ${SOURCE_FILES})

if (NOT WIN32 AND NOT APPLE AND UNIX)
    # Link against libraries
    target_link_libraries(Spheralizer ${WIRINGPI_LIBRARIES})
    target_link_libraries(Spheralizer ${CMAKE_THREAD_LIBS_INIT})
endif ()