#include "print.h"

#include <lua.h>

int laco_printtype(lua_State* L) {
  lua_getglobal(L, "print");
  lua_insert(L, 1);

  return lua_pcall(L, lua_gettop(L) - 1, 0, 0);
}
