cmake_minimum_required(VERSION 2.8)

project(laco)

set(EXECUTABLE_OUTPUT_PATH "${laco_BINARY_DIR}/bin")

set(LACO_VERSION_STRING "0.1.2")
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

  find_library(LACO_LUA luajit-51)

  include_directories("/usr/local/include/luajit-2.0")

  set(LACO_LUA_USED "luajit")
else()
  find_package(Lua51 REQUIRED)

  include_directories(${LUA_INCLUDE_DIR})
  set(LACO_LUA ${LUA_LIBRARIES})

  set(LACO_LUA_USED "lua")
endif()

# for lacoconf includes
include_directories("${laco_BINARY_DIR}/include")

configure_file(
  "${laco_SOURCE_DIR}/src/lacoconf.h.in"
  "${laco_BINARY_DIR}/include/lacoconf.h")

add_subdirectory(src)
