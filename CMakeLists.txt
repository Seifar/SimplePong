cmake_minimum_required(VERSION 3.5)
project(Pong)

set(CMAKE_CXX_STANDARD 11)
#curses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.cpp PongWindow.cpp PongWindow.h PongView.h PongLogic.cpp PongLogic.h PongController.cpp PongController.h)
add_executable(Pong ${SOURCE_FILES})

target_link_libraries(Pong ${CURSES_LIBRARIES})
