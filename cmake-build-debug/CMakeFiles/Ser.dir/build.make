# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Programming\C_Projects\BMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Programming\C_Projects\BMP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ser.dir/flags.make

CMakeFiles/Ser.dir/main.c.obj: CMakeFiles/Ser.dir/flags.make
CMakeFiles/Ser.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Programming\C_Projects\BMP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Ser.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Ser.dir\main.c.obj   -c C:\Programming\C_Projects\BMP\main.c

CMakeFiles/Ser.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ser.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Programming\C_Projects\BMP\main.c > CMakeFiles\Ser.dir\main.c.i

CMakeFiles/Ser.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ser.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Programming\C_Projects\BMP\main.c -o CMakeFiles\Ser.dir\main.c.s

CMakeFiles/Ser.dir/main.c.obj.requires:

.PHONY : CMakeFiles/Ser.dir/main.c.obj.requires

CMakeFiles/Ser.dir/main.c.obj.provides: CMakeFiles/Ser.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\Ser.dir\build.make CMakeFiles/Ser.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/Ser.dir/main.c.obj.provides

CMakeFiles/Ser.dir/main.c.obj.provides.build: CMakeFiles/Ser.dir/main.c.obj


# Object files for target Ser
Ser_OBJECTS = \
"CMakeFiles/Ser.dir/main.c.obj"

# External object files for target Ser
Ser_EXTERNAL_OBJECTS =

Ser.exe: CMakeFiles/Ser.dir/main.c.obj
Ser.exe: CMakeFiles/Ser.dir/build.make
Ser.exe: CMakeFiles/Ser.dir/linklibs.rsp
Ser.exe: CMakeFiles/Ser.dir/objects1.rsp
Ser.exe: CMakeFiles/Ser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Programming\C_Projects\BMP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Ser.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Ser.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ser.dir/build: Ser.exe

.PHONY : CMakeFiles/Ser.dir/build

CMakeFiles/Ser.dir/requires: CMakeFiles/Ser.dir/main.c.obj.requires

.PHONY : CMakeFiles/Ser.dir/requires

CMakeFiles/Ser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Ser.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Ser.dir/clean

CMakeFiles/Ser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Programming\C_Projects\BMP C:\Programming\C_Projects\BMP C:\Programming\C_Projects\BMP\cmake-build-debug C:\Programming\C_Projects\BMP\cmake-build-debug C:\Programming\C_Projects\BMP\cmake-build-debug\CMakeFiles\Ser.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ser.dir/depend

