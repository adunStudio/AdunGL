cmake_minimum_required(VERSION 3.7)

project(AdunGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES main.cpp) # which files should be compiled

add_executable(AdunGL ${SOURCE_FILES})



