# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Petter/documents/computer-graphics-labs/lab2/mathLab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Petter/documents/computer-graphics-labs/lab2/mathLab

# Include any dependencies generated for this target.
include CMakeFiles/mathLab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mathLab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mathLab.dir/flags.make

CMakeFiles/mathLab.dir/main.cpp.o: CMakeFiles/mathLab.dir/flags.make
CMakeFiles/mathLab.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Petter/documents/computer-graphics-labs/lab2/mathLab/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mathLab.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mathLab.dir/main.cpp.o -c /Users/Petter/documents/computer-graphics-labs/lab2/mathLab/main.cpp

CMakeFiles/mathLab.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mathLab.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Petter/documents/computer-graphics-labs/lab2/mathLab/main.cpp > CMakeFiles/mathLab.dir/main.cpp.i

CMakeFiles/mathLab.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mathLab.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Petter/documents/computer-graphics-labs/lab2/mathLab/main.cpp -o CMakeFiles/mathLab.dir/main.cpp.s

# Object files for target mathLab
mathLab_OBJECTS = \
"CMakeFiles/mathLab.dir/main.cpp.o"

# External object files for target mathLab
mathLab_EXTERNAL_OBJECTS =

mathLab: CMakeFiles/mathLab.dir/main.cpp.o
mathLab: CMakeFiles/mathLab.dir/build.make
mathLab: CMakeFiles/mathLab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Petter/documents/computer-graphics-labs/lab2/mathLab/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mathLab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mathLab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mathLab.dir/build: mathLab

.PHONY : CMakeFiles/mathLab.dir/build

CMakeFiles/mathLab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mathLab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mathLab.dir/clean

CMakeFiles/mathLab.dir/depend:
	cd /Users/Petter/documents/computer-graphics-labs/lab2/mathLab && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Petter/documents/computer-graphics-labs/lab2/mathLab /Users/Petter/documents/computer-graphics-labs/lab2/mathLab /Users/Petter/documents/computer-graphics-labs/lab2/mathLab /Users/Petter/documents/computer-graphics-labs/lab2/mathLab /Users/Petter/documents/computer-graphics-labs/lab2/mathLab/CMakeFiles/mathLab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mathLab.dir/depend
