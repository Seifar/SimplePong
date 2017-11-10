cmake_minimum_required(VERSION 3.8)
project(Pong)

set(CMAKE_CXX_STANDARD 11)
#curses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.cpp PongWindow.cpp PongWindow.h cmake-build-debug/PongLogic.cpp cmake-build-debug/PongLogic.h)
add_executable(Pong ${SOURCE_FILES})

target_link_libraries(Pong ${CURSES_LIBRARIES})