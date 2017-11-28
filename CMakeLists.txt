cmake_minimum_required(VERSION 3.7)

project(AdunGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework OpenGL") # compiler version and compiler flags.

set(MAIN_FILES main.cpp AdunGL-Core/graphics/shaders/shader_factory.cpp AdunGL-Core/graphics/shaders/shader_factory.h) # which files should be compiled

file(GLOB ADUNGL-CORE
        AdunGL-Core/graphics/buffers/*.h
        AdunGL-Core/graphics/buffers/*.cpp
        AdunGL-Core/graphics/layers/*.h
        AdunGL-Core/graphics/layers/*.cpp
        AdunGL-Core/graphics/shaders/*.h
        AdunGL-Core/graphics/shaders/*.cpp
        AdunGL-Core/graphics/*.h
        AdunGL-Core/graphics/*.cpp
        AdunGL-Core/maths/*.h
        AdunGL-Core/maths/*.cpp
        AdunGL-Core/utils/*.h
        AdunGL-Core/utils/*.cpp)

file(GLOB EXC_FILES AdunGL-Core/exc/freetype-gl/*.h AdunGL-Core/exc/freetype-gl/*.c)

add_executable(AdunGL ${MAIN_FILES} ${ADUNGL-CORE} ${EXC_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(FREEIMAGE)
target_include_directories (AdunGL PUBLIC ${FREEIMAGE_INCLUDE_DIRS})
target_link_libraries(AdunGL ${FREEIMAGE_LIBRARIES})

find_package(FREETYPE)
target_include_directories (AdunGL PUBLIC ${FREETYPE_INCLUDE_DIR_freetype2})
target_link_libraries(AdunGL ${FREETYPE_LIBRARY})


find_package(FREEGLUT)
target_include_directories (AdunGL PUBLIC ${FREEGLUT_INCLUDE_DIR})
target_link_libraries(AdunGL ${FREEGLUT_LIBRARY})



message("----freeimage----")
message(${FREEIMAGE_FOUND})
message(${FREEIMAGE_INCLUDE_DIRS})
message(${FREEIMAGE_LIBRARY})
message("----freetype----")
message(${FREETYPE_LIBRARY})
message(${FREETYPE_INCLUDE_DIR_freetype2})
message("----freeglut----")
message(${FREEGLUT_INCLUDE_DIR})
message(${FREEGLUT_LIBRARY})