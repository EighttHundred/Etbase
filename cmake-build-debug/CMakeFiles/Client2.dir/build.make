# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/eight/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/eight/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eight/Code/Etbase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eight/Code/Etbase/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Client2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client2.dir/flags.make

CMakeFiles/Client2.dir/test/client2.cpp.o: CMakeFiles/Client2.dir/flags.make
CMakeFiles/Client2.dir/test/client2.cpp.o: ../test/client2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eight/Code/Etbase/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client2.dir/test/client2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client2.dir/test/client2.cpp.o -c /home/eight/Code/Etbase/test/client2.cpp

CMakeFiles/Client2.dir/test/client2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client2.dir/test/client2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eight/Code/Etbase/test/client2.cpp > CMakeFiles/Client2.dir/test/client2.cpp.i

CMakeFiles/Client2.dir/test/client2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client2.dir/test/client2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eight/Code/Etbase/test/client2.cpp -o CMakeFiles/Client2.dir/test/client2.cpp.s

# Object files for target Client2
Client2_OBJECTS = \
"CMakeFiles/Client2.dir/test/client2.cpp.o"

# External object files for target Client2
Client2_EXTERNAL_OBJECTS =

Client2: CMakeFiles/Client2.dir/test/client2.cpp.o
Client2: CMakeFiles/Client2.dir/build.make
Client2: libEtbase.a
Client2: CMakeFiles/Client2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eight/Code/Etbase/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Client2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client2.dir/build: Client2

.PHONY : CMakeFiles/Client2.dir/build

CMakeFiles/Client2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client2.dir/clean

CMakeFiles/Client2.dir/depend:
	cd /home/eight/Code/Etbase/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eight/Code/Etbase /home/eight/Code/Etbase /home/eight/Code/Etbase/cmake-build-debug /home/eight/Code/Etbase/cmake-build-debug /home/eight/Code/Etbase/cmake-build-debug/CMakeFiles/Client2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client2.dir/depend

