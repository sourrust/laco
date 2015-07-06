#include "commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "util.h"

static const char* quit_matches[] = {"quit", "q"};
static const char* help_matches[] = {"help", "?"};

static void print_commands_help() {
  puts("  Commands available:\n");
  puts("    :quit, :q  \tExit laco");
  puts("    :help, :?  \tDisplay this list of commands");
}

static inline bool is_quit(const char* command) {
  return laco_is_match(quit_matches, command);
}

static inline bool is_help(const char* command) {
  return laco_is_match(help_matches, command);
}

void handle_command(struct LacoState* laco, char* line) {
  if(laco != NULL && line != NULL) {
    const char* command = line + 1;

    if(is_quit(command)) {
      laco_kill(laco, 0, "Exiting laco...");
    } else if(is_help(command))  {
      print_commands_help();
    }

    /* Make it seem like this was an empty line */
    line[0] = '\0';
  }
}
