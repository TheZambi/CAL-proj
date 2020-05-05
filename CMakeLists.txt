cmake_minimum_required(VERSION 3.16)
project(CAL_proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL_proj src/main.cpp src/MutablePriorityQueue.h src/Graph.h)