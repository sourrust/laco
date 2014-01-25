#include "laco.h"

#include "lacoconf.h"
#include "commands.h"
#include "util.h"

#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void laco_initLacoState(LacoState* state, int argc, const char** argv) {
  state->version = LACO_VERSION;
  state->argc    = argc;
  state->argv    = argv;
  state->L       = luaL_newstate();
  state->status  = 0;

  if(state->L == NULL) {
    laco_kill(state, -1, "Couldn't initialize lua state.");
  }

  if(state->argc > 1) {
    laco_handleFlag(state);
  }

  luaL_openlibs(state->L);
}

int laco_destroyLacoState(LacoState* state) {
  int result;

  if(state != NULL) {
    if(state->L != NULL) {
      lua_close(state->L);
    }
    result = 1;
  } else {
    result = 0;
  }

  return result;
}
