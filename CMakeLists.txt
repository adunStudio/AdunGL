cmake_minimum_required(VERSION 3.7)

project(AdunGL)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES main.cpp graphics/window.cpp graphics/window.h maths/vec2.cpp maths/vec2.h maths/vec3.cpp maths/vec3.h maths/vec4.cpp maths/vec4.h maths/maths.h maths/mat4.cpp maths/mat4.h maths/math_func.h utils/fileutils.cpp utils/fileutils.cpp utils/fileutils.h graphics/shader.cpp graphics/shader.h) # which files should be compiled


add_executable(AdunGL ${SOURCE_FILES} )

FIND_PATH(GLX_INCLUDE_DIR GL/glx.h PATHS /opt/X11/include /usr/X11/include /usr/X11R6/include)
FIND_LIBRARY(OPENGL_gl_LIBRARY GL PATHS /opt/X11/lib /usr/X11/lib /usr/X11R6/lib)
FIND_LIBRARY(OPENGL_glu_LIBRARY GLU PATHS /opt/X11/lib /usr/X11/lib /usr/X11R6/lib)
LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
INCLUDE_DIRECTORIES(${GLX_INCLUDE_DIR})