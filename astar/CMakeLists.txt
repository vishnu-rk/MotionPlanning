cmake_minimum_required(VERSION 2.8)
project(pathfinding)
#
find_package( OpenCV REQUIRED )
include_directories(include)
#
add_library(implementation src/path_finding.cpp)
add_executable( main src/main.cpp)
target_link_libraries(main implementation)
