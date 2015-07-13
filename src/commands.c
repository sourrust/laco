#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "commands/debugger.h"

static const char* quit_matches[] = {"quit", "q", NULL};
static const char* help_matches[] = {"help", "?", NULL};

/* Debugger commands */
static const char* debug_info_matches[] = {"info", NULL};

static void print_commands_help() {
  puts("  Commands available:\n");
  puts("    :quit, :q     \tExit laco");
  puts("    :help, :?     \tDisplay this list of commands");
  puts("    :info <name>  \tShow information on given function");
}

static inline bool is_quit(const char* command) {
  return laco_is_match(quit_matches, command);
}

static inline bool is_help(const char* command) {
  return laco_is_match(help_matches, command);
}

static inline bool is_debug_info(const char* command) {
  return laco_is_match(debug_info_matches, command);
}

void laco_dispatch(const struct LacoCommand* commands,
                   struct LacoState* laco, const char* command_keyword,
                   const char** arguments) {
  int i;
  const char** matches;

  for(i = 0; (matches = commands[i].matches); i++) {
    if(laco_is_match(matches, command_keyword)) {
      commands[i].handler(laco, arguments);
      break;
    }
  }
}

void laco_handle_command(struct LacoState* laco, char* line) {
  if(laco != NULL && line != NULL) {
    char* command_line   = strdup(line + 1);
    char** command_words = laco_line_to_words(command_line);

    /* Alias for parsed out words within the line */
    const char* command    = command_words[0];
    const char** arguments = (const char**) command_words + 1;

    if(is_quit(command)) {
      laco_kill(laco, 0, "Exiting laco...");
    } else if(is_help(command))  {
      print_commands_help();
    } else if(is_debug_info(command)) {
      laco_print_debug_info(laco, arguments[0]);
    }

    free(command_line);
    free(command_words);

    /* Make it seems like this was an empty line */
    line[0] = '\0';
  }
}
