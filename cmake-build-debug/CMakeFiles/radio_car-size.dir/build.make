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

# Utility rule file for radio_car-size.

# Include the progress variables for this target.
include CMakeFiles/radio_car-size.dir/progress.make

CMakeFiles/radio_car-size: radio_car.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Calculating radio_car image size"
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -DFIRMWARE_IMAGE=/Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/radio_car.elf -DMCU=atmega328p -DEEPROM_IMAGE=/Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/radio_car.eep -P /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

radio_car-size: CMakeFiles/radio_car-size
radio_car-size: CMakeFiles/radio_car-size.dir/build.make

.PHONY : radio_car-size

# Rule to build all files generated by this target.
CMakeFiles/radio_car-size.dir/build: radio_car-size

.PHONY : CMakeFiles/radio_car-size.dir/build

CMakeFiles/radio_car-size.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/radio_car-size.dir/cmake_clean.cmake
.PHONY : CMakeFiles/radio_car-size.dir/clean

CMakeFiles/radio_car-size.dir/depend:
	cd /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oleg/Desktop/projects/Arduino/radio_car /Users/oleg/Desktop/projects/Arduino/radio_car /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug /Users/oleg/Desktop/projects/Arduino/radio_car/cmake-build-debug/CMakeFiles/radio_car-size.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/radio_car-size.dir/depend

