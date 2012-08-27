#include "util.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include "linenoise.h"

static bool incomplete(lua_State* L, int status) {
  bool ret = false;

  if(status == LUA_ERRSYNTAX) {
    const char* mess = lua_tostring(L, -1);

    // Check if the error ends in '<eof>'
    if(strstr(mess, LUA_QL("<eof>")) != NULL) {
      lua_pop(L, 1);
      ret = true;
    }
  }

  return ret;
}

static bool isPrintable(lua_State* L, int status) {
  bool ret = false;

  if(status == LUA_ERRSYNTAX) {
    const char* mess = lua_tostring(L, -1);

    bool isLiteral = strstr(mess,  "unexpected symbol") != NULL;
    bool isVariable = strstr(mess, "'=' expected") != NULL;
    if(isLiteral || isVariable) {
      // pop off error message
      lua_pop(L, 1);

      const char* literal = lua_tostring(L, -1);
      lua_pop(L, 1);

      lua_pushfstring(L, "return %s", literal);

      ret = true;
    }
  }

  return ret;
}

static bool pushline(lua_State* L, bool isFirstLine) {
  char* line = NULL;
  const char* prompt = (isFirstLine) ? "> " : "... ";
  bool ret = false;

  if((line = linenoise(prompt)) != NULL) {
    lua_pushstring(L, line);
    free(line);
    ret = true;
  }

  return ret;
}

int laco_loadline(lua_State* L) {
  int status = 0;
  lua_settop(L, 0);

  if(!pushline(L, true)) return -1;

  // Until complete line
  while(true) {
    status = luaL_loadbuffer(L, lua_tostring(L, 1), lua_strlen(L, 1),
                             "=stdin");

    if(isPrintable(L, status)) continue;
    if(!incomplete(L, status)) break;
    if(!pushline(L, false)) return -1;

    lua_pushliteral(L, "\n");
    lua_insert(L, -2);
    lua_concat(L, 3);
  }
  lua_remove(L, 1);

  return status;
}

void laco_handleline(lua_State* L) {
  int status = 0;

  status = lua_pcall(L, 0, LUA_MULTRET, 0);

  printf("%s\n", lua_typename(L, lua_type(L, -1)));

  if(status) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
}
