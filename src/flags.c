#include "flags.h"

#include <stdio.h>

#include <lauxlib.h>

#include "laco.h"
#include "util.h"

static const char* version_matches[] = {"-v", "--version", NULL};
static const char* help_matches[]    = {"-h", "--help", NULL};

/* Print off the current version of laco */
static void handle_version(LacoState* laco, const char** arguments) {
  assert(laco != NULL);

  const char* version = laco_get_laco_version(laco);

  printf("laco version %s\n", version);
  laco_kill(laco, 0, NULL);
}

/* Print off the help screen */
static void handle_help(LacoState* laco, const char** arguments) {
  assert(laco != NULL);

  puts(
    "A better REPL for Lua.\n\n"
    "Usage: laco [options] [filename]\n\n"
    "-h, --help     Print this help screen\n"
    "-v, --version  Print current version"
  );

  laco_kill(laco, 0, NULL);
}

static const LacoCommand flag_commands[] = {
  { version_matches, handle_version },
  { help_matches,    handle_help },
  { NULL, NULL }
};

/* External API */

void laco_handle_flag(LacoState* laco) {
  assert(laco != NULL);

  lua_State* L        = laco_get_laco_lua_state(laco);
  const char* command = laco_get_laco_args(laco)[1];
  bool was_handled    = laco_dispatch(flag_commands, laco, command, NULL);

  if(!was_handled && luaL_dofile(L, command) != 0) {
    laco_kill(laco, -1,
      "Error: used an unknown flag or file provided doesn't exist");
  }
}
