#include "commands.h"

#include <lauxlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "laco.h"
#include "util.h"
#include "commands/debugger.h"

static const char* quit_matches[]       = {"quit", "q", NULL};
static const char* help_matches[]       = {"help", "?", NULL};
static const char* load_matches[]       = {"load", NULL};
static const char* debug_info_matches[] = {"info", NULL};

static void handle_quit(LacoState* laco, const char** arguments) {
  assert(laco != NULL);

  laco_kill(laco, 0, "Exiting laco...");
}

static void handle_help(LacoState* laco, const char** arguments) {
  puts(
    "  Commands available:\n\n"
    "    :q, :quit     Exit laco\n"
    "    :?, :help     Display this list of commands\n"
    "    :load <file>  Load in the given file name"
    /* "    :info <name>  Show information on given function" */
    );
}

static void handle_load(LacoState* laco, const char** arguments) {
  assert(laco != NULL);

  lua_State* L         = laco_get_laco_lua_state(laco);
  const char* filename = arguments[0];

  if((luaL_dofile(L, filename)) != 0) {
    printf("Couldn't load in file \"%s\"\n", filename);
    lua_pop(L, 1);
  }
}

static void handle_debug_info(LacoState* laco, const char** arguments) {
  assert(laco != NULL);
  assert(arguments != NULL);

  laco_print_debug_info(laco, arguments[0]);
}

static const LacoCommand line_commands[] = {
  { quit_matches, handle_quit },
  { help_matches, handle_help },
  { load_matches, handle_load },

  /* Debugger commands */
  /* { debug_info_matches, handle_debug_info }, */

  { NULL, NULL }
};

/* External API */

void laco_handle_command(LacoState* laco, char* line) {
  assert(laco != NULL);
  assert(line != NULL);

  char* command_line   = strdup(line + 1);
  char** command_words = laco_line_to_words(command_line);

  /* Alias for parsed out words within the line */
  const char* command    = command_words[0];
  const char** arguments = (const char**)command_words + 1;

  laco_dispatch(line_commands, laco, command, arguments);

  free(command_line);
  free(command_words);

  /* Make it seems like this was an empty line */
  line[0] = '\0';
}
