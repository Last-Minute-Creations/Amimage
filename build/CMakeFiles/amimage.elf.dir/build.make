# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
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
CMAKE_SOURCE_DIR = C:\Users\L3k\Amimage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\L3k\Amimage\build

# Include any dependencies generated for this target.
include CMakeFiles/amimage.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/amimage.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/amimage.elf.dir/flags.make

data/amimage.plt: ../res/amimage.pal
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\L3k\Amimage\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating data/amimage.plt"
	cd /d C:\Users\L3k\Amimage && C:\Users\L3k\Amimage\ACE\tools\bin\palette_conv C:/Users/L3k/Amimage/res/amimage.pal C:/Users/L3k/Amimage/build/data/amimage.plt

data/arco32.bm: data/amimage.plt
data/arco32.bm: ../res/arco32.png
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\L3k\Amimage\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating data/arco32.bm"
	cd /d C:\Users\L3k\Amimage && C:\Users\L3k\Amimage\ACE\tools\bin\bitmap_conv C:/Users/L3k/Amimage/build/data/amimage.plt C:/Users/L3k/Amimage/res/arco32.png -o C:/Users/L3k/Amimage/build/data/arco32.bm -i

CMakeFiles/amimage.elf.dir/main.c.obj: CMakeFiles/amimage.elf.dir/flags.make
CMakeFiles/amimage.elf.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\L3k\Amimage\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/amimage.elf.dir/main.c.obj"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\amimage.elf.dir\main.c.obj   -c C:\Users\L3k\Amimage\main.c

CMakeFiles/amimage.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/amimage.elf.dir/main.c.i"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\L3k\Amimage\main.c > CMakeFiles\amimage.elf.dir\main.c.i

CMakeFiles/amimage.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/amimage.elf.dir/main.c.s"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\L3k\Amimage\main.c -o CMakeFiles\amimage.elf.dir\main.c.s

CMakeFiles/amimage.elf.dir/game.c.obj: CMakeFiles/amimage.elf.dir/flags.make
CMakeFiles/amimage.elf.dir/game.c.obj: ../game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\L3k\Amimage\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/amimage.elf.dir/game.c.obj"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\amimage.elf.dir\game.c.obj   -c C:\Users\L3k\Amimage\game.c

CMakeFiles/amimage.elf.dir/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/amimage.elf.dir/game.c.i"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\L3k\Amimage\game.c > CMakeFiles\amimage.elf.dir\game.c.i

CMakeFiles/amimage.elf.dir/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/amimage.elf.dir/game.c.s"
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\bin\m68k-amiga-elf-gcc.exe --sysroot=C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\L3k\Amimage\game.c -o CMakeFiles\amimage.elf.dir\game.c.s

# Object files for target amimage.elf
amimage_elf_OBJECTS = \
"CMakeFiles/amimage.elf.dir/main.c.obj" \
"CMakeFiles/amimage.elf.dir/game.c.obj"

# External object files for target amimage.elf
amimage_elf_EXTERNAL_OBJECTS = \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/audio.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/blit.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/copper.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/game.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/joy.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/key.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/log.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/memory.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/mouse.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/rand.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/state.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/system.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/timer.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/viewport/camera.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/viewport/scrollbuffer.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/viewport/simplebuffer.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/managers/viewport/tilebuffer.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/bitmap.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/bmframe.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/chunky.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/custom.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/dir.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/extview.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/file.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/font.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/palette.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/ptplayer.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/ace/utils/tag.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fix16.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fix16_exp.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fix16_sqrt.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fix16_str.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fix16_trig.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/fract32.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/fixmath/uint32.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/bartman/gcc8_a_support.s.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/bartman/gcc8_c_support.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/ctype.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/errno.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/intrin.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/printf.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/stdio_file.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/stdio_putchar.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/stdlib.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/string.c.obj" \
"C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/src/mini_std/strtoul.c.obj"

amimage.elf: CMakeFiles/amimage.elf.dir/main.c.obj
amimage.elf: CMakeFiles/amimage.elf.dir/game.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/audio.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/blit.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/copper.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/game.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/joy.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/key.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/log.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/memory.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/mouse.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/rand.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/state.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/system.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/timer.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/viewport/camera.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/viewport/scrollbuffer.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/viewport/simplebuffer.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/managers/viewport/tilebuffer.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/bitmap.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/bmframe.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/chunky.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/custom.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/dir.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/extview.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/file.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/font.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/palette.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/ptplayer.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/ace/utils/tag.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fix16.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fix16_exp.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fix16_sqrt.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fix16_str.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fix16_trig.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/fract32.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/fixmath/uint32.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/bartman/gcc8_a_support.s.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/bartman/gcc8_c_support.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/ctype.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/errno.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/intrin.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/printf.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/stdio_file.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/stdio_putchar.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/stdlib.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/string.c.obj
amimage.elf: ace/CMakeFiles/ace.dir/src/mini_std/strtoul.c.obj
amimage.elf: CMakeFiles/amimage.elf.dir/build.make
amimage.elf: CMakeFiles/amimage.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\L3k\Amimage\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable amimage.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\amimage.elf.dir\link.txt --verbose=$(VERBOSE)
	C:\Users\L3k\.vscode\extensions\bartmanabyss.amiga-debug-1.1.0-preview11\bin\opt\..\elf2hunk.exe amimage.elf amimage.exe

# Rule to build all files generated by this target.
CMakeFiles/amimage.elf.dir/build: amimage.elf

.PHONY : CMakeFiles/amimage.elf.dir/build

CMakeFiles/amimage.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\amimage.elf.dir\cmake_clean.cmake
.PHONY : CMakeFiles/amimage.elf.dir/clean

CMakeFiles/amimage.elf.dir/depend: data/amimage.plt
CMakeFiles/amimage.elf.dir/depend: data/arco32.bm
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\L3k\Amimage C:\Users\L3k\Amimage C:\Users\L3k\Amimage\build C:\Users\L3k\Amimage\build C:\Users\L3k\Amimage\build\CMakeFiles\amimage.elf.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/amimage.elf.dir/depend

