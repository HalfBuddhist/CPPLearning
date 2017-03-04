cmake_minimum_required(VERSION 3.4)
project(GCD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    GCD.cpp
    GCD.h
    Main.cpp)

add_executable(GCD ${SOURCE_FILES})