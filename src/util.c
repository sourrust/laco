#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "laco.h"

static inline void ignore_extra(const char chr, char** string_ptr) {
  assert(string_ptr != NULL);

  while(*string_ptr != NULL && **string_ptr == chr) {
    *string_ptr += 1;
  }
}

/* External API */

void laco_kill(LacoState* laco, int status, const char* message) {
  assert(laco != NULL);

  laco_destroy_laco_state(laco);

  if(message != NULL) {
    fprintf(stderr, "%s\n", message);
  }

  exit(status);
}

bool laco_is_match(const char** matches, const char* test_string) {
  assert(matches != NULL);
  assert(test_string != NULL);

  int i;
  const char* match;

  for(i = 0; (match = matches[i]); i++) {
    if(strcmp(test_string, match) == 0) {
      return true;
    }
  }

  return false;
}

char** laco_split_by(const char split_with, char* string,
                     int ignore_repeats) {
  assert(string != NULL);

  size_t i;
  char** result = calloc(16, sizeof(char*));

  for(i = 0; (result[i] = strsep(&string, &split_with)); i++) {
    if(ignore_repeats) {
      ignore_extra(split_with, &string);
    }
  }

  return result;
}

bool laco_dispatch(const LacoCommand* commands, LacoState* laco,
                   const char* command_keyword, const char** arguments) {
  assert(commands != NULL);
  assert(laco != NULL);
  assert(command_keyword != NULL);

  int i;
  const LacoCommand* command;
  const char** matches;
  LacoHandler handler;

  for(i = 0; (command = &commands[i]); i++) {
    matches = command->matches;
    handler = command->handler;

    if((matches != NULL && handler != NULL) &&
        laco_is_match(matches, command_keyword)) {
      handler(laco, arguments);
      return true;
    }
  }

  return false;
}
