# Try to find the FREEGLUT library
#
# FREEGLUT_INCLUDE_DIR
# FREEGLUT_LIBRARY
# FREEGLUT_FOUND
FIND_PATH(
        FREEGLUT_INCLUDE_DIR freeglut.h
        PATHS
        ${PROJECT_SOURCE_DIR}/Dependency/freeglut/include/GL
)

FIND_LIBRARY(
        FREEGLUT_LIBRARY libglut.dylib
        PATH
        ${PROJECT_SOURCE_DIR}/Dependency/freeglut/lib
        NO_DEFAULT_PATH
)

MARK_AS_ADVANCED(FREEGLUT_INCLUDE_DIR FREEGLUT_LIBRARY)