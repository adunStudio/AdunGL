cmake_minimum_required(VERSION 3.7)

# 프로젝트 이름 설정
#
project(AdunGL)

# 변수 정의
# SET ( <변수명> <값> )
# <값>에 공백이 포함되어 있는 경우, 큰따옴표 "..."로 둘러주면 된다.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

# 목록 변수 정의
# <항목>들은 공백문자로 구분한다.
# <항목>값에 공백이 포함되어 있는 경우, 역시 큰따옴표로 둘러주면 된다. 목록 변수의 항목들은 기본적으로 세미콜론(;)으로 구분되어 저장된다
set(SOURCE_FILES texture_test.cpp AdunGL-Core/graphics/window.cpp AdunGL-Core/graphics/window.h AdunGL-Core/maths/vec2.cpp AdunGL-Core/maths/vec2.h AdunGL-Core/maths/vec3.cpp AdunGL-Core/maths/vec3.h AdunGL-Core/maths/vec4.cpp AdunGL-Core/maths/vec4.h AdunGL-Core/maths/maths.h AdunGL-Core/maths/mat4.cpp AdunGL-Core/maths/mat4.h AdunGL-Core/maths/math_func.h AdunGL-Core/utils/fileutils.cpp AdunGL-Core/utils/fileutils.cpp AdunGL-Core/utils/fileutils.h AdunGL-Core/graphics/shader.cpp AdunGL-Core/graphics/shader.h AdunGL-Core/graphics/buffers/buffer.cpp AdunGL-Core/graphics/buffers/buffer.h AdunGL-Core/graphics/buffers/indexBuffer.cpp AdunGL-Core/graphics/buffers/indexBuffer.h AdunGL-Core/graphics/buffers/vertexArray.cpp AdunGL-Core/graphics/buffers/vertexArray.h AdunGL-Core/graphics/camera.cpp AdunGL-Core/graphics/camera.h AdunGL-Core/graphics/renderable2d.h AdunGL-Core/graphics/renderer2d.h AdunGL-Core/graphics/simple2drenderer.cpp AdunGL-Core/graphics/simple2drenderer.h AdunGL-Core/graphics/batchrenderer2d.cpp AdunGL-Core/graphics/batchrenderer2d.h AdunGL-Core/graphics/sprite.cpp AdunGL-Core/graphics/sprite.h AdunGL-Core/graphics/static_sprite.cpp AdunGL-Core/graphics/static_sprite.h AdunGL-Core/src.h AdunGL-Core/utils/timer.cpp AdunGL-Core/utils/timer.h AdunGL-Core/graphics/layers/layer.cpp AdunGL-Core/graphics/layers/layer.h AdunGL-Core/graphics/layers/tilelayer.cpp AdunGL-Core/graphics/layers/tilelayer.h AdunGL-Core/graphics/layers/group.cpp AdunGL-Core/graphics/layers/group.h AdunGL-Core/utils/imageload.cpp AdunGL-Core/utils/imageload.h AdunGL-Core/graphics/texture.cpp AdunGL-Core/graphics/texture.h) # which files should be compiled

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


find_package(FREEIMAGE)

add_executable(AdunGL ${SOURCE_FILES})


target_include_directories (AdunGL PUBLIC ${FREEIMAGE_INCLUDE_DIRS})
target_link_libraries(AdunGL ${FREEIMAGE_LIBRARIES})


# 변수 참조
# 변수를 참조하고자 할 때는 다음과 같이 변수명 앞에 $를 붙이거나, ${...}로 둘러 주면 된다.
# $변수명 or ${<변수명>}

message(${FREEIMAGE_FOUND})
message(${FREEIMAGE_INCLUDE_DIRS})
message(${FREEIMAGE_LIBRARY})