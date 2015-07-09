#include "debugger.h"

#include <stdio.h>
#include <lua.h>

#include "laco.h"

void laco_print_debug_info(struct LacoState* laco,
                           const char* function_name) {
  lua_State* L = laco_get_laco_lua_state(laco);
  lua_Debug debug_info = {0};

  lua_getfield(L, LUA_GLOBALSINDEX, function_name);

  lua_getinfo(L, ">Sl", &debug_info);

  printf(
    "What:            \t%s\n"
    "Source file:     \t%s\n"
    "Line defined on: \t%d\n"
    "Current line:    \t%d\n",
    debug_info.what, debug_info.source,
    debug_info.linedefined, debug_info.currentline);
}
