include_directories("${laco_SOURCE_DIR}/src")

set(SOURCE main.c flags.c laco.c
           util.c util/print.c util/line.c
           commands.c commands/debugger.c)

add_executable(laco ${SOURCE})
target_link_libraries(laco ${LACO_LUA} linenoise)

install(TARGETS laco
  RUNTIME DESTINATION bin)
