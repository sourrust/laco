#include "util.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include "linenoise.h"
#include "laco.h"
#include "util/print.h"

typedef struct LacoState LacoState;

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

    linenoiseHistoryAdd(line);
    free(line);
    ret = true;
  }

  return ret;
}

int laco_loadline(LacoState* state) {
  int status = 0;
  lua_State* L = laco_getLuaState(state);

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

void laco_handleline(LacoState* state) {
  int status = 0;
  lua_State* L = laco_getLuaState(state);

  status = lua_pcall(L, 0, LUA_MULTRET, 0);

  if(status == 0 && lua_gettop(L) > 0)
    status = laco_printtype(L);

  if(status) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
}

void laco_kill(LacoState* state, int status, const char* message) {
  laco_deleteLacoState(state);

  if(message != NULL) {
    fprintf(stderr, "%s\n", message);
  }

  exit(status);
}
