#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "commands.h"
#include "util.h"

int main(int argc, const char** argv) {
  lua_State* L = luaL_newstate();

  if(L == NULL) {
    puts("Couldn't initialize lua state");
    return -1;
  }

  if(argc > 0) {
    laco_handleFlag(L, argv[0]);
  }

  luaL_openlibs(L);

  while(laco_loadline(L) != -1) {
    laco_handleline(L);
  }

  lua_close(L);
  return 0;
}
