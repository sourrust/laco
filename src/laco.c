#include "laco.h"

#include "lacoconf.h"
#include "commands.h"
#include "util.h"

#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

struct LacoState {
  lua_State* L;
  const char* version;

  int argc;
  const char** argv;
};

typedef struct LacoState LacoState;

LacoState* laco_newLacoState(int argc, const char** argv) {
  LacoState* state = malloc(sizeof(LacoState));

  state->version = LACO_VERSION;
  state->argc    = argc;
  state->argv    = argv;
  state->L       = luaL_newstate();

  if(state->L == NULL) {
    laco_kill(state->L, -1, "Couldn't initialize lua state.");
  }

  if(state->argc > 1) {
    laco_handleFlag(state->L, state->argv[1]);
  }

  luaL_openlibs(state->L);

  return state;
}

int laco_deleteLacoState(LacoState* state) {
  int result;

  if(state != NULL) {
    lua_close(state->L);
    free(state);

    state = NULL;
    result = 1;
  } else {
    result = 0;
  }

  return result;
}

lua_State* laco_getLuaState(LacoState* state) {
  return state->L;
}
