FIND_PATH(FREETYPE_INCLUDE_DIR_ft2build ft2build.h
        HINTS
        $ENV{FREETYPE_DIR}
        PATH_SUFFIXES include
        PATHS
        /usr/local/X11R6/include
        /usr/local/X11/include
        /usr/X11/include
        /sw/include
        /opt/local/include
        /usr/freeware/include
        ${PROJECT_SOURCE_DIR}/Dependency/freetype/include
        )

FIND_PATH(FREETYPE_INCLUDE_DIR_freetype2 freetype/config/ftheader.h
        HINTS
        $ENV{FREETYPE_DIR}/include/freetype2
        PATHS
        /usr/local/X11R6/include
        /usr/local/X11/include
        /usr/X11/include
        /sw/include
        /opt/local/include
        /usr/freeware/include
        ${PROJECT_SOURCE_DIR}/Dependency/freetype/include
        PATH_SUFFIXES freetype2
        )

FIND_LIBRARY(FREETYPE_LIBRARY
        NAMES freetype libfreetype freetype219 freetype239
        HINTS
        $ENV{FREETYPE_DIR}
        PATH_SUFFIXES lib64 lib
        PATHS
        /usr/local/X11R6
        /usr/local/X11
        ${PROJECT_SOURCE_DIR}/Dependency/freetype
        /usr/X11
        /sw
        /usr/freeware
        )

# set the user variables
IF(FREETYPE_INCLUDE_DIR_ft2build AND FREETYPE_INCLUDE_DIR_freetype2)
    SET(FREETYPE_INCLUDE_DIRS "${FREETYPE_INCLUDE_DIR_ft2build};${FREETYPE_INCLUDE_DIR_freetype2}")
ENDIF(FREETYPE_INCLUDE_DIR_ft2build AND FREETYPE_INCLUDE_DIR_freetype2)
SET(FREETYPE_LIBRARIES "${FREETYPE_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set FREETYPE_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Freetype  DEFAULT_MSG  FREETYPE_LIBRARY  FREETYPE_INCLUDE_DIRS)


MARK_AS_ADVANCED(FREETYPE_LIBRARY FREETYPE_INCLUDE_DIR_freetype2 FREETYPE_INCLUDE_DIR_ft2build)