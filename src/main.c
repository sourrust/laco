#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "util.h"

int main() {
  lua_State* L = luaL_newstate();

  if(L == NULL) {
    puts("Couldn't initialize lua state");
    return -1;
  }

  luaL_openlibs(L);

  while(laco_loadline(L) != -1) {
    laco_handleline(L);
  }

  lua_close(L);
  return 0;
}
