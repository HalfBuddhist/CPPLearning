cmake_minimum_required(VERSION 3.4)
project(CCPPSoup)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Test.h
        OutputControl.cpp
        QSortInC.cpp
        RangeOfNumber.cpp
        SortInCPP.cpp
        Test.cpp
        Inheritance.cpp VirtualFunc.cpp Class.cpp PrivateFuncOverload/Father.cpp PrivateFuncOverload/Father.h
        PrivateFuncOverload/Son.cpp PrivateFuncOverload/Son.h PrivateFuncOverload/TestPrivateOverload.cpp
        Initialize.cpp Initialize.h)

add_executable(CCPPSoup ${SOURCE_FILES})