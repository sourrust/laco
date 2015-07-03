set(DEPS_DIR "${laco_SOURCE_DIR}/deps")

include_directories("${DEPS_DIR}/linenoise")

set(SOURCE ${DEPS_DIR}/linenoise/linenoise.c
           main.c util.c util/print.c
           flags.c commands.c laco.c)

add_executable(laco ${SOURCE})
target_link_libraries(laco ${LACO_LUA})

install(TARGETS laco
  RUNTIME DESTINATION bin)
