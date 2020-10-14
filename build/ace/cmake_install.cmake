# Install script for directory: C:/Users/L3k/Amimage/ACE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/L3k/.vscode/extensions/bartmanabyss.amiga-debug-1.1.0-preview11/bin/opt/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/ace" TYPE FILE FILES
    "src/ace/managers/audio.c.obj"
    "src/ace/managers/blit.c.obj"
    "src/ace/managers/copper.c.obj"
    "src/ace/managers/game.c.obj"
    "src/ace/managers/joy.c.obj"
    "src/ace/managers/key.c.obj"
    "src/ace/managers/log.c.obj"
    "src/ace/managers/memory.c.obj"
    "src/ace/managers/mouse.c.obj"
    "src/ace/managers/rand.c.obj"
    "src/ace/managers/state.c.obj"
    "src/ace/managers/system.c.obj"
    "src/ace/managers/timer.c.obj"
    "src/ace/managers/viewport/camera.c.obj"
    "src/ace/managers/viewport/scrollbuffer.c.obj"
    "src/ace/managers/viewport/simplebuffer.c.obj"
    "src/ace/managers/viewport/tilebuffer.c.obj"
    "src/ace/utils/bitmap.c.obj"
    "src/ace/utils/bmframe.c.obj"
    "src/ace/utils/chunky.c.obj"
    "src/ace/utils/custom.c.obj"
    "src/ace/utils/dir.c.obj"
    "src/ace/utils/extview.c.obj"
    "src/ace/utils/file.c.obj"
    "src/ace/utils/font.c.obj"
    "src/ace/utils/palette.c.obj"
    "src/ace/utils/ptplayer.c.obj"
    "src/ace/utils/tag.c.obj"
    "src/fixmath/fix16.c.obj"
    "src/fixmath/fix16_exp.c.obj"
    "src/fixmath/fix16_sqrt.c.obj"
    "src/fixmath/fix16_str.c.obj"
    "src/fixmath/fix16_trig.c.obj"
    "src/fixmath/fract32.c.obj"
    "src/fixmath/uint32.c.obj"
    "src/bartman/gcc8_a_support.s.obj"
    "src/bartman/gcc8_c_support.c.obj"
    "src/mini_std/ctype.c.obj"
    "src/mini_std/errno.c.obj"
    "src/mini_std/intrin.c.obj"
    "src/mini_std/printf.c.obj"
    "src/mini_std/stdio_file.c.obj"
    "src/mini_std/stdio_putchar.c.obj"
    "src/mini_std/stdlib.c.obj"
    "src/mini_std/string.c.obj"
    "src/mini_std/strtoul.c.obj"
    FILES_FROM_DIR "C:/Users/L3k/Amimage/build/ace/CMakeFiles/ace.dir/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/ace/macros.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/generic" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/ace/generic/main.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/generic/screen.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/utils" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/bitmap.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/bmframe.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/chunky.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/custom.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/dir.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/endian.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/extview.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/file.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/font.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/mini_std.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/palette.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/ptplayer.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/utils/tag.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/managers" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/audio.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/blit.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/copper.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/game.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/joy.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/key.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/log.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/memory.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/mouse.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/rand.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/state.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/system.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/timer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/managers/viewport" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/viewport/camera.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/viewport/scrollbuffer.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/viewport/simplebuffer.h"
    "C:/Users/L3k/Amimage/ACE/include/ace/managers/viewport/tilebuffer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fixmath" TYPE FILE FILES
    "C:/Users/L3k/Amimage/ACE/include/fixmath/fix16.h"
    "C:/Users/L3k/Amimage/ACE/include/fixmath/fix16_trig_sin_lut.h"
    "C:/Users/L3k/Amimage/ACE/include/fixmath/fixmath.h"
    "C:/Users/L3k/Amimage/ACE/include/fixmath/fract32.h"
    "C:/Users/L3k/Amimage/ACE/include/fixmath/int64.h"
    "C:/Users/L3k/Amimage/ACE/include/fixmath/uint32.h"
    )
endif()

