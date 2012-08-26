#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "util.h"

int main() {
  int error = 0;
  lua_State* L = luaL_newstate();

  if(L == NULL) {
    puts("Couldn't initialize lua state");
    return -1;
  }

  luaL_openlibs(L);

  while((error = laco_loadline(L)) != -1) {
    error = lua_pcall(L, 0, LUA_MULTRET, 0);
    if(error) {
      fprintf(stderr, "%s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
    }
  }

  lua_close(L);
  return 0;
}
