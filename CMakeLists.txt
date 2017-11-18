cmake_minimum_required(VERSION 3.7)

project(AdunGL)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES main.cpp AdunGL-Core/graphics/window.cpp AdunGL-Core/graphics/window.h AdunGL-Core/maths/vec2.cpp AdunGL-Core/maths/vec2.h AdunGL-Core/maths/vec3.cpp AdunGL-Core/maths/vec3.h AdunGL-Core/maths/vec4.cpp AdunGL-Core/maths/vec4.h AdunGL-Core/maths/maths.h AdunGL-Core/maths/mat4.cpp AdunGL-Core/maths/mat4.h AdunGL-Core/maths/math_func.h AdunGL-Core/utils/fileutils.cpp AdunGL-Core/utils/fileutils.cpp AdunGL-Core/utils/fileutils.h AdunGL-Core/graphics/shader.cpp AdunGL-Core/graphics/shader.h AdunGL-Core/graphics/buffers/buffer.cpp AdunGL-Core/graphics/buffers/buffer.h AdunGL-Core/graphics/buffers/indexBuffer.cpp AdunGL-Core/graphics/buffers/indexBuffer.h AdunGL-Core/graphics/buffers/vertexArray.cpp AdunGL-Core/graphics/buffers/vertexArray.h AdunGL-Core/graphics/camera.cpp AdunGL-Core/graphics/camera.h AdunGL-Core/graphics/renderable2d.h AdunGL-Core/graphics/renderer2d.h AdunGL-Core/graphics/simple2drenderer.cpp AdunGL-Core/graphics/simple2drenderer.h AdunGL-Core/graphics/batchrenderer2d.cpp AdunGL-Core/graphics/batchrenderer2d.h AdunGL-Core/graphics/sprite.cpp AdunGL-Core/graphics/sprite.h AdunGL-Core/graphics/static_sprite.cpp AdunGL-Core/graphics/static_sprite.h AdunGL-Core/src.h AdunGL-Core/utils/timer.cpp AdunGL-Core/utils/timer.h) # which files should be compiled


add_executable(AdunGL ${SOURCE_FILES} )

FIND_PATH(GLX_INCLUDE_DIR GL/glx.h PATHS /opt/X11/include /usr/X11/include /usr/X11R6/include)
FIND_LIBRARY(OPENGL_gl_LIBRARY GL PATHS /opt/X11/lib /usr/X11/lib /usr/X11R6/lib)
FIND_LIBRARY(OPENGL_glu_LIBRARY GLU PATHS /opt/X11/lib /usr/X11/lib /usr/X11R6/lib)
LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
INCLUDE_DIRECTORIES(${GLX_INCLUDE_DIR})