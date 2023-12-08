cmake_minimum_required(VERSION 3.27)
project(LoTI)

set(CMAKE_CXX_STANDARD 17)

add_executable(LoTI src/main.cpp "src/image.cpp" )

add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")