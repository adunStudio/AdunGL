# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/adun/Desktop/AdunGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/adun/Desktop/AdunGL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AdunGL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AdunGL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AdunGL.dir/flags.make

CMakeFiles/AdunGL.dir/main.cpp.o: CMakeFiles/AdunGL.dir/flags.make
CMakeFiles/AdunGL.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/adun/Desktop/AdunGL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AdunGL.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AdunGL.dir/main.cpp.o -c /Users/adun/Desktop/AdunGL/main.cpp

CMakeFiles/AdunGL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AdunGL.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adun/Desktop/AdunGL/main.cpp > CMakeFiles/AdunGL.dir/main.cpp.i

CMakeFiles/AdunGL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AdunGL.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adun/Desktop/AdunGL/main.cpp -o CMakeFiles/AdunGL.dir/main.cpp.s

CMakeFiles/AdunGL.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/AdunGL.dir/main.cpp.o.requires

CMakeFiles/AdunGL.dir/main.cpp.o.provides: CMakeFiles/AdunGL.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AdunGL.dir/build.make CMakeFiles/AdunGL.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AdunGL.dir/main.cpp.o.provides

CMakeFiles/AdunGL.dir/main.cpp.o.provides.build: CMakeFiles/AdunGL.dir/main.cpp.o


CMakeFiles/AdunGL.dir/graphics/window.cpp.o: CMakeFiles/AdunGL.dir/flags.make
CMakeFiles/AdunGL.dir/graphics/window.cpp.o: ../graphics/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/adun/Desktop/AdunGL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AdunGL.dir/graphics/window.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AdunGL.dir/graphics/window.cpp.o -c /Users/adun/Desktop/AdunGL/graphics/window.cpp

CMakeFiles/AdunGL.dir/graphics/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AdunGL.dir/graphics/window.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adun/Desktop/AdunGL/graphics/window.cpp > CMakeFiles/AdunGL.dir/graphics/window.cpp.i

CMakeFiles/AdunGL.dir/graphics/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AdunGL.dir/graphics/window.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adun/Desktop/AdunGL/graphics/window.cpp -o CMakeFiles/AdunGL.dir/graphics/window.cpp.s

CMakeFiles/AdunGL.dir/graphics/window.cpp.o.requires:

.PHONY : CMakeFiles/AdunGL.dir/graphics/window.cpp.o.requires

CMakeFiles/AdunGL.dir/graphics/window.cpp.o.provides: CMakeFiles/AdunGL.dir/graphics/window.cpp.o.requires
	$(MAKE) -f CMakeFiles/AdunGL.dir/build.make CMakeFiles/AdunGL.dir/graphics/window.cpp.o.provides.build
.PHONY : CMakeFiles/AdunGL.dir/graphics/window.cpp.o.provides

CMakeFiles/AdunGL.dir/graphics/window.cpp.o.provides.build: CMakeFiles/AdunGL.dir/graphics/window.cpp.o


# Object files for target AdunGL
AdunGL_OBJECTS = \
"CMakeFiles/AdunGL.dir/main.cpp.o" \
"CMakeFiles/AdunGL.dir/graphics/window.cpp.o"

# External object files for target AdunGL
AdunGL_EXTERNAL_OBJECTS =

AdunGL: CMakeFiles/AdunGL.dir/main.cpp.o
AdunGL: CMakeFiles/AdunGL.dir/graphics/window.cpp.o
AdunGL: CMakeFiles/AdunGL.dir/build.make
AdunGL: CMakeFiles/AdunGL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/adun/Desktop/AdunGL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AdunGL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AdunGL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AdunGL.dir/build: AdunGL

.PHONY : CMakeFiles/AdunGL.dir/build

CMakeFiles/AdunGL.dir/requires: CMakeFiles/AdunGL.dir/main.cpp.o.requires
CMakeFiles/AdunGL.dir/requires: CMakeFiles/AdunGL.dir/graphics/window.cpp.o.requires

.PHONY : CMakeFiles/AdunGL.dir/requires

CMakeFiles/AdunGL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AdunGL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AdunGL.dir/clean

CMakeFiles/AdunGL.dir/depend:
	cd /Users/adun/Desktop/AdunGL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/adun/Desktop/AdunGL /Users/adun/Desktop/AdunGL /Users/adun/Desktop/AdunGL/cmake-build-debug /Users/adun/Desktop/AdunGL/cmake-build-debug /Users/adun/Desktop/AdunGL/cmake-build-debug/CMakeFiles/AdunGL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AdunGL.dir/depend

