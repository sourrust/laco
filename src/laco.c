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
  return (laco == NULL) ? NULL : laco->state;
}

const char* laco_get_laco_version(LacoState* laco) {
  return (laco == NULL) ? NULL : laco->version;
}

const char** laco_get_laco_args(LacoState* laco) {
  return (laco == NULL) ? NULL : laco->argv;
}

int laco_get_laco_status(LacoState* laco) {
  return (laco == NULL) ? -1 : laco->status;
}

void laco_set_laco_status(LacoState* laco, int status) {
  if(laco != NULL) {
    laco->status = status;
  }
}
