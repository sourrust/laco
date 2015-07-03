#include "commands.h"

#include <string.h>

#include "util.h"

void handle_command(struct LacoState* laco, char* line) {
  if(laco != NULL && line != NULL) {
    const char* command = line + 1;

    if(strcmp(command, "quit") == 0) {
      laco_kill(laco, 0, "Exiting laco...");
    } else {
      /* Make it seem like this was an empty line */
      line[0] = '\0';
    }
  }
}
