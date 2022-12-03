cmake_minimum_required(VERSION 3.16)

project(DispatchQueue)

# set compiler
set(CMAKE_CXX_COMPILER /usr/bin/clang++-10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -fsanitize=address -pthread")


# set build files
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
        src/main.cpp
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/DispatchQueue.cpp
        )

set(PROJECT_HEADERS
        ${PROJECT_INCLUDE_DIR}/DispatchQueue.h
        ${PROJECT_INCLUDE_DIR}/TypeErasure.h

        )

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})


#target_link_libraries( ${PROJECT_NAME} )