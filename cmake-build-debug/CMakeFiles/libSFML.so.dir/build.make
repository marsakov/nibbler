# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/msakovyc/nibbler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/msakovyc/nibbler/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/libSFML.so.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libSFML.so.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libSFML.so.dir/flags.make

CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o: CMakeFiles/libSFML.so.dir/flags.make
CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o: ../src/SFMLGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o -c /Users/msakovyc/nibbler/src/SFMLGraph.cpp

CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msakovyc/nibbler/src/SFMLGraph.cpp > CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.i

CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msakovyc/nibbler/src/SFMLGraph.cpp -o CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.s

# Object files for target libSFML.so
libSFML_so_OBJECTS = \
"CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o"

# External object files for target libSFML.so
libSFML_so_EXTERNAL_OBJECTS =

liblibSFML.so.dylib: CMakeFiles/libSFML.so.dir/src/SFMLGraph.cpp.o
liblibSFML.so.dylib: CMakeFiles/libSFML.so.dir/build.make
liblibSFML.so.dylib: CMakeFiles/libSFML.so.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library liblibSFML.so.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libSFML.so.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libSFML.so.dir/build: liblibSFML.so.dylib

.PHONY : CMakeFiles/libSFML.so.dir/build

CMakeFiles/libSFML.so.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libSFML.so.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libSFML.so.dir/clean

CMakeFiles/libSFML.so.dir/depend:
	cd /Users/msakovyc/nibbler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/msakovyc/nibbler /Users/msakovyc/nibbler /Users/msakovyc/nibbler/cmake-build-debug /Users/msakovyc/nibbler/cmake-build-debug /Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles/libSFML.so.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libSFML.so.dir/depend

