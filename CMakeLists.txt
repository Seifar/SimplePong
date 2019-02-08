cmake_minimum_required(VERSION 3.5)
project(Pong)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES main.cpp Pong.cpp Pong.h Window.cpp Window.h)
add_executable(Pong ${SOURCE_FILES})

target_link_libraries(Pong ${SDL2_LIBRARY} -pthread )
