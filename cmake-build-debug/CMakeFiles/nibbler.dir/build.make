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
include CMakeFiles/nibbler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nibbler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nibbler.dir/flags.make

CMakeFiles/nibbler.dir/src/Game.cpp.o: CMakeFiles/nibbler.dir/flags.make
CMakeFiles/nibbler.dir/src/Game.cpp.o: ../src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nibbler.dir/src/Game.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nibbler.dir/src/Game.cpp.o -c /Users/msakovyc/nibbler/src/Game.cpp

CMakeFiles/nibbler.dir/src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nibbler.dir/src/Game.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msakovyc/nibbler/src/Game.cpp > CMakeFiles/nibbler.dir/src/Game.cpp.i

CMakeFiles/nibbler.dir/src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nibbler.dir/src/Game.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msakovyc/nibbler/src/Game.cpp -o CMakeFiles/nibbler.dir/src/Game.cpp.s

CMakeFiles/nibbler.dir/src/main.cpp.o: CMakeFiles/nibbler.dir/flags.make
CMakeFiles/nibbler.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nibbler.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nibbler.dir/src/main.cpp.o -c /Users/msakovyc/nibbler/src/main.cpp

CMakeFiles/nibbler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nibbler.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msakovyc/nibbler/src/main.cpp > CMakeFiles/nibbler.dir/src/main.cpp.i

CMakeFiles/nibbler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nibbler.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msakovyc/nibbler/src/main.cpp -o CMakeFiles/nibbler.dir/src/main.cpp.s

CMakeFiles/nibbler.dir/src/Snake.cpp.o: CMakeFiles/nibbler.dir/flags.make
CMakeFiles/nibbler.dir/src/Snake.cpp.o: ../src/Snake.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nibbler.dir/src/Snake.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nibbler.dir/src/Snake.cpp.o -c /Users/msakovyc/nibbler/src/Snake.cpp

CMakeFiles/nibbler.dir/src/Snake.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nibbler.dir/src/Snake.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msakovyc/nibbler/src/Snake.cpp > CMakeFiles/nibbler.dir/src/Snake.cpp.i

CMakeFiles/nibbler.dir/src/Snake.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nibbler.dir/src/Snake.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msakovyc/nibbler/src/Snake.cpp -o CMakeFiles/nibbler.dir/src/Snake.cpp.s

# Object files for target nibbler
nibbler_OBJECTS = \
"CMakeFiles/nibbler.dir/src/Game.cpp.o" \
"CMakeFiles/nibbler.dir/src/main.cpp.o" \
"CMakeFiles/nibbler.dir/src/Snake.cpp.o"

# External object files for target nibbler
nibbler_EXTERNAL_OBJECTS =

nibbler: CMakeFiles/nibbler.dir/src/Game.cpp.o
nibbler: CMakeFiles/nibbler.dir/src/main.cpp.o
nibbler: CMakeFiles/nibbler.dir/src/Snake.cpp.o
nibbler: CMakeFiles/nibbler.dir/build.make
nibbler: CMakeFiles/nibbler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable nibbler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nibbler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nibbler.dir/build: nibbler

.PHONY : CMakeFiles/nibbler.dir/build

CMakeFiles/nibbler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nibbler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nibbler.dir/clean

CMakeFiles/nibbler.dir/depend:
	cd /Users/msakovyc/nibbler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/msakovyc/nibbler /Users/msakovyc/nibbler /Users/msakovyc/nibbler/cmake-build-debug /Users/msakovyc/nibbler/cmake-build-debug /Users/msakovyc/nibbler/cmake-build-debug/CMakeFiles/nibbler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nibbler.dir/depend

