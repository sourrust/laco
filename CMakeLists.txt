cmake_minimum_required(VERSION 2.8)

project(laco)

set(EXECUTABLE_OUTPUT_PATH "${laco_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/cmake/modules")

set(LACO_VERSION_STRING "0.2.0")
execute_process(COMMAND "date" "+%a %b %d, %Y %T"
  OUTPUT_VARIABLE LACO_TIMESTAMP)

string(REGEX REPLACE "\n" "" LACO_TIMESTAMP ${LACO_TIMESTAMP})

option(LACO_USE_LUAJIT "Use luajit libraries." off)

if(LACO_USE_LUAJIT)
  # When using Mac OSX for x64 applications, you need these flags linked
  # against the binary for luajit library to allocate a luaState.
  #
  # ====================================================================
  #
  # <http://luajit.org/install.html#embed>
  if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS
        "-pagezero_size 10000 -image_base 100000000")
  endif()

  find_package(LuaJIT REQUIRED)

  include_directories(${LUAJIT_INCLUDE_DIR})
  set(LACO_LUA ${LUAJIT_LIBRARY})

  set(LACO_LUA_USED "luajit")
else()
  find_package(Lua51 REQUIRED)

  include_directories(${LUA_INCLUDE_DIR})
  set(LACO_LUA ${LUA_LIBRARY})

  set(LACO_LUA_USED "lua")
endif()

# for lacoconf includes
include_directories("${laco_BINARY_DIR}/include")

configure_file(
  "${laco_SOURCE_DIR}/src/lacoconf.h.in"
  "${laco_BINARY_DIR}/include/lacoconf.h")

# for linenoise library
include_directories("${laco_SOURCE_DIR}/deps/linenoise")
add_subdirectory(deps)

add_subdirectory(src)
