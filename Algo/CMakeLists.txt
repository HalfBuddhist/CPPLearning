cmake_minimum_required(VERSION 3.4)
project(Algo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES  Graph/Dijkstra/structure.h  Graph/Dijkstra/usual.h Graph/Dijkstra/Dijkstra.c)
#set(SOURCE_FILES  Graph/DAGShortestPath.cpp)
#set(SOURCE_FILES  Graph/DAGShortestPath.cpp)
#set(SOURCE_FILES  IterativeTraversalTree2.cpp)
#set(SOURCE_FILES  MorrisTraversal.cpp)
set(SOURCE_FILES  Tree/SegmentTree.cpp)



add_executable(Algo ${SOURCE_FILES})