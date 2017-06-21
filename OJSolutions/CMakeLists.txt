cmake_minimum_required(VERSION 3.4)
project(OJSolutions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES poj/2823_SlidingWindow.cpp)

#set(SOURCE_FILES jobdu/1372_MaxSumInSubArray.cpp)

#set(SOURCE_FILES leetcode/29_DivideTwoIntegers.cpp general.h)
#set(SOURCE_FILES tencent/first.cpp)
set(SOURCE_FILES  tencent/remote_interview/subset_bitset.cpp)
#set(SOURCE_FILES main.cpp)

add_executable(OJSolutions ${SOURCE_FILES})