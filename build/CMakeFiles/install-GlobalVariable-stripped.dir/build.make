# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saahil/Desktop/CD7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saahil/Desktop/CD7/build

# Utility rule file for install-GlobalVariable-stripped.

# Include the progress variables for this target.
include CMakeFiles/install-GlobalVariable-stripped.dir/progress.make

CMakeFiles/install-GlobalVariable-stripped:
	/usr/bin/cmake -DCMAKE_INSTALL_COMPONENT="GlobalVariable" -DCMAKE_INSTALL_DO_STRIP=1 -P /home/saahil/Desktop/CD7/build/cmake_install.cmake

install-GlobalVariable-stripped: CMakeFiles/install-GlobalVariable-stripped
install-GlobalVariable-stripped: CMakeFiles/install-GlobalVariable-stripped.dir/build.make

.PHONY : install-GlobalVariable-stripped

# Rule to build all files generated by this target.
CMakeFiles/install-GlobalVariable-stripped.dir/build: install-GlobalVariable-stripped

.PHONY : CMakeFiles/install-GlobalVariable-stripped.dir/build

CMakeFiles/install-GlobalVariable-stripped.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/install-GlobalVariable-stripped.dir/cmake_clean.cmake
.PHONY : CMakeFiles/install-GlobalVariable-stripped.dir/clean

CMakeFiles/install-GlobalVariable-stripped.dir/depend:
	cd /home/saahil/Desktop/CD7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saahil/Desktop/CD7 /home/saahil/Desktop/CD7 /home/saahil/Desktop/CD7/build /home/saahil/Desktop/CD7/build /home/saahil/Desktop/CD7/build/CMakeFiles/install-GlobalVariable-stripped.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/install-GlobalVariable-stripped.dir/depend

