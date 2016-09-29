cmake_minimum_required(VERSION 3.6)
project(Calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -DDEBUG")

set(SOURCE_FILES main.cpp Queue.cpp Queue.h Node.cpp Node.h Stack.cpp Stack.h)
add_executable(Calculator ${SOURCE_FILES})