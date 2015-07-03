#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "util.h"

static void print_commands_help() {
  puts("  Commands available:\n");
  puts("    :quit   \tExit laco");
  puts("    :help   \tDisplay this list of commands");
}

void handle_command(struct LacoState* laco, char* line) {
  if(laco != NULL && line != NULL) {
    const char* command = line + 1;

    if(strcmp(command, "quit") == 0) {
      laco_kill(laco, 0, "Exiting laco...");
    } else if(strcmp(command, "help") == 0)  {
      print_commands_help();
    }

    /* Make it seem like this was an empty line */
    line[0] = '\0';
  }
}
