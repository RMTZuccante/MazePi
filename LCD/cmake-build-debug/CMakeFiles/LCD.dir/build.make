# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/pi/Downloads/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/pi/Downloads/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/LCD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/LCD/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LCD.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LCD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LCD.dir/flags.make

CMakeFiles/LCD.dir/main.cpp.o: CMakeFiles/LCD.dir/flags.make
CMakeFiles/LCD.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/LCD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LCD.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LCD.dir/main.cpp.o -c /home/pi/Desktop/LCD/main.cpp

CMakeFiles/LCD.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LCD.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/LCD/main.cpp > CMakeFiles/LCD.dir/main.cpp.i

CMakeFiles/LCD.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LCD.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/LCD/main.cpp -o CMakeFiles/LCD.dir/main.cpp.s

CMakeFiles/LCD.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/LCD.dir/main.cpp.o.requires

CMakeFiles/LCD.dir/main.cpp.o.provides: CMakeFiles/LCD.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LCD.dir/build.make CMakeFiles/LCD.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/LCD.dir/main.cpp.o.provides

CMakeFiles/LCD.dir/main.cpp.o.provides.build: CMakeFiles/LCD.dir/main.cpp.o


CMakeFiles/LCD.dir/lcd_i2c.c.o: CMakeFiles/LCD.dir/flags.make
CMakeFiles/LCD.dir/lcd_i2c.c.o: ../lcd_i2c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/LCD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LCD.dir/lcd_i2c.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LCD.dir/lcd_i2c.c.o   -c /home/pi/Desktop/LCD/lcd_i2c.c

CMakeFiles/LCD.dir/lcd_i2c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCD.dir/lcd_i2c.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/LCD/lcd_i2c.c > CMakeFiles/LCD.dir/lcd_i2c.c.i

CMakeFiles/LCD.dir/lcd_i2c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCD.dir/lcd_i2c.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/LCD/lcd_i2c.c -o CMakeFiles/LCD.dir/lcd_i2c.c.s

CMakeFiles/LCD.dir/lcd_i2c.c.o.requires:

.PHONY : CMakeFiles/LCD.dir/lcd_i2c.c.o.requires

CMakeFiles/LCD.dir/lcd_i2c.c.o.provides: CMakeFiles/LCD.dir/lcd_i2c.c.o.requires
	$(MAKE) -f CMakeFiles/LCD.dir/build.make CMakeFiles/LCD.dir/lcd_i2c.c.o.provides.build
.PHONY : CMakeFiles/LCD.dir/lcd_i2c.c.o.provides

CMakeFiles/LCD.dir/lcd_i2c.c.o.provides.build: CMakeFiles/LCD.dir/lcd_i2c.c.o


# Object files for target LCD
LCD_OBJECTS = \
"CMakeFiles/LCD.dir/main.cpp.o" \
"CMakeFiles/LCD.dir/lcd_i2c.c.o"

# External object files for target LCD
LCD_EXTERNAL_OBJECTS =

LCD: CMakeFiles/LCD.dir/main.cpp.o
LCD: CMakeFiles/LCD.dir/lcd_i2c.c.o
LCD: CMakeFiles/LCD.dir/build.make
LCD: CMakeFiles/LCD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/LCD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable LCD"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LCD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LCD.dir/build: LCD

.PHONY : CMakeFiles/LCD.dir/build

CMakeFiles/LCD.dir/requires: CMakeFiles/LCD.dir/main.cpp.o.requires
CMakeFiles/LCD.dir/requires: CMakeFiles/LCD.dir/lcd_i2c.c.o.requires

.PHONY : CMakeFiles/LCD.dir/requires

CMakeFiles/LCD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LCD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LCD.dir/clean

CMakeFiles/LCD.dir/depend:
	cd /home/pi/Desktop/LCD/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/LCD /home/pi/Desktop/LCD /home/pi/Desktop/LCD/cmake-build-debug /home/pi/Desktop/LCD/cmake-build-debug /home/pi/Desktop/LCD/cmake-build-debug/CMakeFiles/LCD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LCD.dir/depend

