cmake_minimum_required(VERSION 3.5)
project(Pong)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Pong.cpp Pong.h Window.cpp Window.h)
add_executable(Pong ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})


find_package(SFML 2 REQUIRED network audio graphics window system)
find_package(Threads)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Pong ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(Pong ${CMAKE_THREAD_LIBS_INIT} )
