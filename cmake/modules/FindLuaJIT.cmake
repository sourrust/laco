find_path(LUAJIT_INCLUDE_DIR luajit.h
  HINTS
    ENV LUAJIT_DIR
  PATH_SUFFIXES
    include/luajit-2.0 include/luajit2.0 include/luajit include
  PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
)

find_library(LUAJIT_LIBRARY
  NAMES luajit-51 luajit-5.1 luajit
  HINTS
    ENV LUAJIT_DIR
  PATH_SUFFIXES lib
  PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr/
    /sw
    /opt/local
    /opt/csw
    /opt
)

if(LUAJIT_LIBRARY)
  # include the math library for Unix
  if(UNIX AND NOT APPLE AND NOT BEOS)
    find_library(LUAJIT_MATH_LIBRARY m)
    set( LUAJIT_LIBRARY "${LUAJIT_LIBRARY};${LUAJIT_MATH_LIBRARY}" CACHE STRING "Lua Libraries")
  # For Windows and Mac, don't need to explicitly include the math library
  else()
    set( LUAJIT_LIBRARY "${LUAJIT_LIBRARY}" CACHE STRING "Lua Libraries")
  endif()
endif()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LUA_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaJIT
  REQUIRED_VARS LUAJIT_LIBRARY LUAJIT_INCLUDE_DIR
  VERSION_VAR LUAJIT_VERSION_STRING)

mark_as_advanced(
  LUAJIT_INCLUDE_DIR LUAJIT_LIBRARIES LUAJIT_LIBRARY LUAJIT_MATH_LIBRARY)
