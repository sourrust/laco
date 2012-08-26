set(DEPS_DIR "${laco_SOURCE_DIR}/deps")

include_directories("${DEPS_DIR}/linenoise")

set(SOURCE ${DEPS_DIR}/linenoise/linenoise.c
           main.c)

add_executable(laco ${SOURCE})
target_link_libraries(laco ${LUA})
