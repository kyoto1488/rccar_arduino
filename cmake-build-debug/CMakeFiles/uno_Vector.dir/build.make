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
CMAKE_SOURCE_DIR = /Users/oleg/Desktop/projects/Arduino/radio_car

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/uno_Vector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uno_Vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uno_Vector.dir/flags.make

CMakeFiles/uno_Vector.dir/command/command.cpp.obj: CMakeFiles/uno_Vector.dir/flags.make
CMakeFiles/uno_Vector.dir/command/command.cpp.obj: ../command/command.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uno_Vector.dir/command/command.cpp.obj"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uno_Vector.dir/command/command.cpp.obj -c /Users/oleg/Desktop/projects/Arduino/radio_car/command/command.cpp

CMakeFiles/uno_Vector.dir/command/command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_Vector.dir/command/command.cpp.i"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oleg/Desktop/projects/Arduino/radio_car/command/command.cpp > CMakeFiles/uno_Vector.dir/command/command.cpp.i

CMakeFiles/uno_Vector.dir/command/command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_Vector.dir/command/command.cpp.s"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oleg/Desktop/projects/Arduino/radio_car/command/command.cpp -o CMakeFiles/uno_Vector.dir/command/command.cpp.s

# Object files for target uno_Vector
uno_Vector_OBJECTS = \
"CMakeFiles/uno_Vector.dir/command/command.cpp.obj"

# External object files for target uno_Vector
uno_Vector_EXTERNAL_OBJECTS =

libuno_Vector.a: CMakeFiles/uno_Vector.dir/command/command.cpp.obj
libuno_Vector.a: CMakeFiles/uno_Vector.dir/build.make
libuno_Vector.a: CMakeFiles/uno_Vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libuno_Vector.a"
	$(CMAKE_COMMAND) -P CMakeFiles/uno_Vector.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uno_Vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uno_Vector.dir/build: libuno_Vector.a

.PHONY : CMakeFiles/uno_Vector.dir/build

CMakeFiles/uno_Vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uno_Vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uno_Vector.dir/clean

CMakeFiles/uno_Vector.dir/depend:
	cd /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oleg/Desktop/projects/Arduino/radio_car /Users/oleg/Desktop/projects/Arduino/radio_car /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles/uno_Vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uno_Vector.dir/depend

