# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gtq/GTQ_pmsm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gtq/GTQ_pmsm/build

# Include any dependencies generated for this target.
include CMakeFiles/onestep_without_delay.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/onestep_without_delay.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/onestep_without_delay.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/onestep_without_delay.dir/flags.make

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o: ../example/onestep_without_delay.cpp
CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o -MF CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o -c /home/gtq/GTQ_pmsm/example/onestep_without_delay.cpp

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/example/onestep_without_delay.cpp > CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.i

CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/example/onestep_without_delay.cpp -o CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.s

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o: ../src/PMSM.cpp
CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o -c /home/gtq/GTQ_pmsm/src/PMSM.cpp

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/PMSM.cpp > CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.i

CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/PMSM.cpp -o CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.s

CMakeFiles/onestep_without_delay.dir/src/client.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/client.cpp.o: ../src/client.cpp
CMakeFiles/onestep_without_delay.dir/src/client.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/client.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/client.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/client.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/client.cpp.o -c /home/gtq/GTQ_pmsm/src/client.cpp

CMakeFiles/onestep_without_delay.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/client.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/client.cpp > CMakeFiles/onestep_without_delay.dir/src/client.cpp.i

CMakeFiles/onestep_without_delay.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/client.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/client.cpp -o CMakeFiles/onestep_without_delay.dir/src/client.cpp.s

CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o: ../src/controller.cpp
CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o -c /home/gtq/GTQ_pmsm/src/controller.cpp

CMakeFiles/onestep_without_delay.dir/src/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/controller.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/controller.cpp > CMakeFiles/onestep_without_delay.dir/src/controller.cpp.i

CMakeFiles/onestep_without_delay.dir/src/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/controller.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/controller.cpp -o CMakeFiles/onestep_without_delay.dir/src/controller.cpp.s

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o: ../src/current_controller.cpp
CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o -c /home/gtq/GTQ_pmsm/src/current_controller.cpp

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/current_controller.cpp > CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.i

CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/current_controller.cpp -o CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.s

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o: ../src/inverter.cpp
CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o -c /home/gtq/GTQ_pmsm/src/inverter.cpp

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/inverter.cpp > CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.i

CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/inverter.cpp -o CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.s

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o: ../src/speed_control.cpp
CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o -c /home/gtq/GTQ_pmsm/src/speed_control.cpp

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/speed_control.cpp > CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.i

CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/speed_control.cpp -o CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.s

CMakeFiles/onestep_without_delay.dir/src/system.cpp.o: CMakeFiles/onestep_without_delay.dir/flags.make
CMakeFiles/onestep_without_delay.dir/src/system.cpp.o: ../src/system.cpp
CMakeFiles/onestep_without_delay.dir/src/system.cpp.o: CMakeFiles/onestep_without_delay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/onestep_without_delay.dir/src/system.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/onestep_without_delay.dir/src/system.cpp.o -MF CMakeFiles/onestep_without_delay.dir/src/system.cpp.o.d -o CMakeFiles/onestep_without_delay.dir/src/system.cpp.o -c /home/gtq/GTQ_pmsm/src/system.cpp

CMakeFiles/onestep_without_delay.dir/src/system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onestep_without_delay.dir/src/system.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gtq/GTQ_pmsm/src/system.cpp > CMakeFiles/onestep_without_delay.dir/src/system.cpp.i

CMakeFiles/onestep_without_delay.dir/src/system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onestep_without_delay.dir/src/system.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gtq/GTQ_pmsm/src/system.cpp -o CMakeFiles/onestep_without_delay.dir/src/system.cpp.s

# Object files for target onestep_without_delay
onestep_without_delay_OBJECTS = \
"CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/client.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o" \
"CMakeFiles/onestep_without_delay.dir/src/system.cpp.o"

# External object files for target onestep_without_delay
onestep_without_delay_EXTERNAL_OBJECTS =

onestep_without_delay: CMakeFiles/onestep_without_delay.dir/example/onestep_without_delay.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/PMSM.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/client.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/controller.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/current_controller.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/inverter.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/speed_control.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/src/system.cpp.o
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/build.make
onestep_without_delay: CMakeFiles/onestep_without_delay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gtq/GTQ_pmsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable onestep_without_delay"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/onestep_without_delay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/onestep_without_delay.dir/build: onestep_without_delay
.PHONY : CMakeFiles/onestep_without_delay.dir/build

CMakeFiles/onestep_without_delay.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/onestep_without_delay.dir/cmake_clean.cmake
.PHONY : CMakeFiles/onestep_without_delay.dir/clean

CMakeFiles/onestep_without_delay.dir/depend:
	cd /home/gtq/GTQ_pmsm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gtq/GTQ_pmsm /home/gtq/GTQ_pmsm /home/gtq/GTQ_pmsm/build /home/gtq/GTQ_pmsm/build /home/gtq/GTQ_pmsm/build/CMakeFiles/onestep_without_delay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/onestep_without_delay.dir/depend

