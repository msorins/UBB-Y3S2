# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug

# Utility rule file for WatershedProject_autogen.

# Include the progress variables for this target.
include CMakeFiles/WatershedProject_autogen.dir/progress.make

CMakeFiles/WatershedProject_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target WatershedProject"
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E cmake_autogen /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug/CMakeFiles/WatershedProject_autogen.dir/AutogenInfo.cmake Debug

WatershedProject_autogen: CMakeFiles/WatershedProject_autogen
WatershedProject_autogen: CMakeFiles/WatershedProject_autogen.dir/build.make

.PHONY : WatershedProject_autogen

# Rule to build all files generated by this target.
CMakeFiles/WatershedProject_autogen.dir/build: WatershedProject_autogen

.PHONY : CMakeFiles/WatershedProject_autogen.dir/build

CMakeFiles/WatershedProject_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WatershedProject_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WatershedProject_autogen.dir/clean

CMakeFiles/WatershedProject_autogen.dir/depend:
	cd /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug /Users/so/Desktop/Y3S2/ImageProcessing/WatershedProject/cmake-build-debug/CMakeFiles/WatershedProject_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WatershedProject_autogen.dir/depend

