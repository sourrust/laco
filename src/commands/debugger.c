#include "debugger.h"

#include <lua.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "laco.h"
#include "util.h"

void laco_print_debug_info(LacoState* laco, const char* function_name) {
  assert(laco != NULL);
  assert(function_name != NULL);

  int i;
  char* namespace;
  lua_State* L         = laco_get_laco_lua_state(laco);
  size_t index         = LUA_GLOBALSINDEX;
  lua_Debug debug_info = {0};

  char* name        = strdup(function_name);
  char** namespaces = laco_split_by('.', name, 0);

  /* Walk down the namespace if there is something to go down */
  for(i = 0; (namespace = namespaces[i]); i++) {
    lua_getfield(L, index, namespace);

    index = lua_gettop(L);

    if(lua_type(L, index) == LUA_TNIL) {
      printf("Couldn't find the function named \"%s\"\n", function_name);
      lua_pop(L, i + 1);

      return;
    }
  }

  lua_getinfo(L, ">Sl", &debug_info);

  printf(
    "What:            \t%s\n"
    "Source file:     \t%s\n"
    "Line defined on: \t%d\n"
    "Current line:    \t%d\n",
    debug_info.what, debug_info.source, debug_info.linedefined,
    debug_info.currentline);

  /* Pop off the extra fields from the top of the stack */
  if(i > 1) {
    lua_pop(L, i - 1);
  }

  free(name);
  free(namespaces);
}
