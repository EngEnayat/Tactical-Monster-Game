# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug

# Utility rule file for GamePhase_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/GamePhase_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GamePhase_autogen.dir/progress.make

CMakeFiles/GamePhase_autogen: GamePhase_autogen/timestamp

GamePhase_autogen/timestamp: /home/enayatullah-balaghi/Qt/6.8.2/gcc_64/libexec/moc
GamePhase_autogen/timestamp: /home/enayatullah-balaghi/Qt/6.8.2/gcc_64/libexec/uic
GamePhase_autogen/timestamp: CMakeFiles/GamePhase_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target GamePhase"
	/usr/bin/cmake -E cmake_autogen /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug/CMakeFiles/GamePhase_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug/GamePhase_autogen/timestamp

GamePhase_autogen: CMakeFiles/GamePhase_autogen
GamePhase_autogen: GamePhase_autogen/timestamp
GamePhase_autogen: CMakeFiles/GamePhase_autogen.dir/build.make
.PHONY : GamePhase_autogen

# Rule to build all files generated by this target.
CMakeFiles/GamePhase_autogen.dir/build: GamePhase_autogen
.PHONY : CMakeFiles/GamePhase_autogen.dir/build

CMakeFiles/GamePhase_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GamePhase_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GamePhase_autogen.dir/clean

CMakeFiles/GamePhase_autogen.dir/depend:
	cd /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug /home/enayatullah-balaghi/Downloads/QT/QtExcercise/GamePhase/build/Extra-Debug/CMakeFiles/GamePhase_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GamePhase_autogen.dir/depend

