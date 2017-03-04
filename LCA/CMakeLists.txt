cmake_minimum_required(VERSION 3.4)
project(Template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES FindInOneTravle.cpp)
#set(SOURCE_FILES ComparePath.cpp)
add_executable(LCA ${SOURCE_FILES})