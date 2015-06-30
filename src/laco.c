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

LacoState* laco_new_laco_state(int argc, const char** argv) {
  LacoState* laco = malloc(sizeof(LacoState));

  laco->version = LACO_VERSION;
  laco->argc    = argc;
  laco->argv    = argv;
  laco->state   = luaL_newstate();
  laco->status  = 0;

  if(laco->state == NULL) {
    laco_kill(laco, -1, "Couldn't initialize lua state.");
  }

  if(laco->argc > 1) {
    laco_handle_flag(laco);
  }

  luaL_openlibs(laco->state);

  return laco;
}

int laco_destroy_laco_state(LacoState* laco) {
  int result;

  if(laco != NULL) {
    if(laco->state != NULL) {
      lua_close(laco->state);
    }
    free(laco);

    result = 1;
  } else {
    result = 0;
  }

  return result;
}

struct lua_State* laco_get_laco_lua_state(LacoState* laco) {
  struct lua_State* result;

  result = (laco == NULL) ? NULL : laco->state;

  return result;
}

const char* laco_get_laco_version(LacoState* laco) {
  const char* result;

  result = (laco == NULL) ? NULL : laco->version;

  return result;
}

const char** laco_get_laco_args(LacoState* laco) {
  const char** result;

  result = (laco == NULL) ? NULL : laco->argv;

  return result;
}

int laco_get_laco_status(LacoState* laco) {
  int result;

  result = (laco == NULL) ? -1 : laco->status;

  return result;
}

void laco_set_laco_status(LacoState* laco, int status) {
  if(laco == NULL) return;

  laco->status = status;
}
