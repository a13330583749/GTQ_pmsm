# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\codes\GTQ_pmsm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\codes\GTQ_pmsm\build

# Include any dependencies generated for this target.
include CMakeFiles/onestep_without_delay.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/onestep_without_delay.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/onestep_without_delay.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/onestep_without_delay.dir/flags.make

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj: D:/codes/GTQ_pmsm/example/onestep_without_delay.cpp
CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\example\onestep_without_delay.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\example\onestep_without_delay.cpp.obj -c D:\codes\GTQ_pmsm\example\onestep_without_delay.cpp

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\example\onestep_without_delay.cpp > CMakeFiles\onestep_without_delay.dir\example\onestep_without_delay.cpp.i

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\example\onestep_without_delay.cpp -o CMakeFiles\onestep_without_delay.dir\example\onestep_without_delay.cpp.s

CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj: D:/codes/GTQ_pmsm/src/Compensator.cpp
CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\Compensator.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\Compensator.cpp.obj -c D:\codes\GTQ_pmsm\src\Compensator.cpp

CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\Compensator.cpp > CMakeFiles\onestep_without_delay.dir\src\Compensator.cpp.i

CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\Compensator.cpp -o CMakeFiles\onestep_without_delay.dir\src\Compensator.cpp.s

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj: D:/codes/GTQ_pmsm/src/PMSM.cpp
CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\PMSM.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\PMSM.cpp.obj -c D:\codes\GTQ_pmsm\src\PMSM.cpp

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\PMSM.cpp > CMakeFiles\onestep_without_delay.dir\src\PMSM.cpp.i

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\PMSM.cpp -o CMakeFiles\onestep_without_delay.dir\src\PMSM.cpp.s

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj: D:/codes/GTQ_pmsm/src/current_controller.cpp
CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\current_controller.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\current_controller.cpp.obj -c D:\codes\GTQ_pmsm\src\current_controller.cpp

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\current_controller.cpp > CMakeFiles\onestep_without_delay.dir\src\current_controller.cpp.i

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\current_controller.cpp -o CMakeFiles\onestep_without_delay.dir\src\current_controller.cpp.s

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj: D:/codes/GTQ_pmsm/src/inverter.cpp
CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\inverter.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\inverter.cpp.obj -c D:\codes\GTQ_pmsm\src\inverter.cpp

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\inverter.cpp > CMakeFiles\onestep_without_delay.dir\src\inverter.cpp.i

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\inverter.cpp -o CMakeFiles\onestep_without_delay.dir\src\inverter.cpp.s

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj: D:/codes/GTQ_pmsm/src/speed_control.cpp
CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\speed_control.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\speed_control.cpp.obj -c D:\codes\GTQ_pmsm\src\speed_control.cpp

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\speed_control.cpp > CMakeFiles\onestep_without_delay.dir\src\speed_control.cpp.i

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\speed_control.cpp -o CMakeFiles\onestep_without_delay.dir\src\speed_control.cpp.s

CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj: D:/codes/GTQ_pmsm/src/system.cpp
CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj -MF CMakeFiles\onestep_without_delay.dir\src\system.cpp.obj.d -o CMakeFiles\onestep_without_delay.dir\src\system.cpp.obj -c D:\codes\GTQ_pmsm\src\system.cpp

CMakeFiles/onestep_without_delay.dir/src/system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/system.cpp.i"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\codes\GTQ_pmsm\src\system.cpp > CMakeFiles\onestep_without_delay.dir\src\system.cpp.i

CMakeFiles/onestep_without_delay.dir/src/system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/system.cpp.s"
	C:\MinGW\bin\g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\codes\GTQ_pmsm\src\system.cpp -o CMakeFiles\onestep_without_delay.dir\src\system.cpp.s

# Object files for target onestep_without_delay
onestep_without_delay_OBJECTS = \
"CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj" \
"CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj"

# External object files for target onestep_without_delay
onestep_without_delay_EXTERNAL_OBJECTS =

onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/Compensator.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/src/system.cpp.obj
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/build.make
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/linkLibs.rsp
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/objects1.rsp
onestep_without_delay.exe: CMakeFiles/onestep_without_delay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\codes\GTQ_pmsm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable onestep_without_delay.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\onestep_without_delay.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/onestep_without_delay.dir/build: onestep_without_delay.exe
.PHONY : CMakeFiles/onestep_without_delay.dir/build

CMakeFiles/onestep_without_delay.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\onestep_without_delay.dir\cmake_clean.cmake
.PHONY : CMakeFiles/onestep_without_delay.dir/clean

CMakeFiles/onestep_without_delay.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\codes\GTQ_pmsm D:\codes\GTQ_pmsm D:\codes\GTQ_pmsm\build D:\codes\GTQ_pmsm\build D:\codes\GTQ_pmsm\build\CMakeFiles\onestep_without_delay.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/onestep_without_delay.dir/depend

