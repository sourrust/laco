#include "laco.h"

#include "lacoconf.h"
#include "commands.h"
#include "util.h"

#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

struct LacoState {
  struct lua_State* state;
  const char* version;

  int argc;
  const char** argv;

  int status;
};

typedef struct LacoState LacoState;

LacoState* laco_newLacoState(int argc, const char** argv) {
  LacoState* state = malloc(sizeof(LacoState));

  state->version = LACO_VERSION;
  state->argc    = argc;
  state->argv    = argv;
  state->state   = luaL_newstate();
  state->status  = 0;

  if(state->L == NULL) {
    laco_kill(state, -1, "Couldn't initialize lua state.");
  }

  if(state->argc > 1) {
    laco_handleFlag(state);
  }

  luaL_openlibs(state->state);

  return state;
}

int laco_destroyLacoState(LacoState* state) {
  int result;

  if(state != NULL) {
    if(state->state != NULL) {
      lua_close(state->state);
    }
    free(state);

    result = 1;
  } else {
    result = 0;
  }

  return result;
}

struct lua_State* laco_getLacoLuaState(struct LacoState* state) {
  struct lua_State* result;

  result = (state == NULL) ? NULL : state->state;

  return result;
}

const char* laco_getLacoVersion(struct LacoState* state) {
  const char* result;

  result = (state == NULL) ? NULL : state->version;

  return result;
}

const char** laco_getLacoArgs(struct LacoState* state) {
  const char** result;

  result = (state == NULL) ? NULL : state->argv;

  return result;
}

int laco_getLacoStatus(struct LacoState* state) {
  int result;

  result = (state == NULL) ? -1 : state->status;

  return result;
}

void laco_setLacoStatus(struct LacoState* state, int status) {
  if(state == NULL) return;

  state->status = status;
}
