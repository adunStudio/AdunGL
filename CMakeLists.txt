cmake_minimum_required(VERSION 3.7)

project(AdunGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES main.cpp graphics/window.cpp graphics/window.h maths/vec2.cpp maths/vec2.h maths/vec3.cpp maths/vec3.h maths/vec4.cpp maths/vec4.h maths/maths.h) # which files should be compiled

add_executable(AdunGL ${SOURCE_FILES} )



