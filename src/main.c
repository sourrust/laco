#include <stdlib.h>
#include <string.h>

#include "linenoise.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


int main() {
  char* line = NULL;
  int error = 0;
  lua_State* L = luaL_newstate();

  if(L == NULL) {
    puts("Couldn't initialize lua state");
    return -1;
  }

  luaL_openlibs(L);

  while((line = linenoise("> ")) != NULL) {
    error = luaL_loadstring(L, line) || lua_pcall(L, 0, 0, 0);
    if(error) {
      fprintf(stderr, "%s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
    }

    free(line);
  }

  lua_close(L);
  return 0;
}
