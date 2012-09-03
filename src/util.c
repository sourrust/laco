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

void reportError(lua_State* L, int status) {
  if(status != 0 && lua_isstring(L, -1)) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    fflush(stderr);
    lua_pop(L, 1);
  }
}

static bool incomplete(lua_State* L, int status) {
  bool result = false;

  if(status == LUA_ERRSYNTAX) {
    size_t lmess;
    const char* mess = lua_tolstring(L, -1, &lmess);

    /* Check if the error ends in '<eof>' */
    size_t eofsize = sizeof(LUA_QL("<eof>")) - 1;
    const char* mess_end = mess + lmess - eofsize;
    if(strstr(mess, LUA_QL("<eof>")) == mess_end) {
      lua_pop(L, 1);
      result = true;
    }
  }

  return result;
}

static bool isPrintable(lua_State* L, int status) {
  bool result = false;

  if(status == LUA_ERRSYNTAX) {
    const char* mess = lua_tostring(L, -1);

    bool isLiteral = strstr(mess,  "unexpected symbol") != NULL;
    bool isVariable = strstr(mess, "'=' expected") != NULL;
    if(isLiteral || isVariable) {
      /* pop off error message */
      lua_pop(L, 1);

      const char* literal = lua_tostring(L, -1);
      lua_pop(L, 1);

      lua_pushfstring(L, "return %s", literal);

      result = true;
    }
  } else if(lua_type(L, -1) == LUA_TFUNCTION) {
    const char* func = lua_tostring(L, -2);

    /* check for a return statement */
    if(!strstr(func, "return ")) {
      lua_pop(L, 2);
      lua_pushfstring(L, "return %s", func);

      result = true;
    }
  }

  return result;
}

static bool pushline(lua_State* L, bool isFirstLine) {
  char* line = NULL;
  const char* prompt = (isFirstLine) ? "> " : "... ";
  bool result = false;

  if((line = linenoise(prompt)) != NULL) {
    lua_pushstring(L, line);

    linenoiseHistoryAdd(line);
    free(line);
    result = true;
  }

  return result;
}

int laco_loadline(LacoState* state) {
  int status = state->status;
  lua_State* L = state->L;

  lua_settop(L, 0);

  if(!pushline(L, true)) return -1;

  /* Until complete line */
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
  state->status = status;

  return status;
}

void laco_handleline(LacoState* state) {
  int status = state->status;
  lua_State* L = state->L;

  if(status == 0) {
    status = lua_pcall(L, 0, LUA_MULTRET, 0);
  }

  reportError(L, status);

  if(status == 0 && lua_gettop(L) > 0)
    status = laco_printtype(L);

  reportError(L, status);

  state->status = status;
}

void laco_kill(LacoState* state, int status, const char* message) {
  laco_destroyLacoState(state);

  if(message != NULL) {
    fprintf(stderr, "%s\n", message);
  }

  exit(status);
}
