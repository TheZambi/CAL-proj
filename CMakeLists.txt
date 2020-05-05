cmake_minimum_required(VERSION 3.16)
project(CAL_proj)

set(CMAKE_CXX_STANDARD 14)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)


include_directories(src/lib)
include_directories(src/resources)

add_executable(CAL_proj src/main.cpp src/MutablePriorityQueue.h src/Graph.h src/lib/connection.cpp src/lib/graphviewer.cpp)