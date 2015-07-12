#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "laco.h"

static inline void ignore_extra(const char chr, char** string_ptr) {
  if(*string_ptr == NULL) return;

  while(**string_ptr == chr) {
    *string_ptr += 1;
  }
}

/* External API */

void laco_kill(LacoState* laco, int status, const char* message) {
  laco_destroy_laco_state(laco);

  if(message != NULL) {
    fprintf(stderr, "%s\n", message);
  }

  exit(status);
}

bool laco_is_match(const char** matches, const char* test_string) {
  int i;
  char* match;

  for(i = 0; (match = (char*) matches[i]); i++) {
    if(strcmp(test_string, match) == 0) {
      return true;
    }
  }

  return false;
}

char** laco_split_by(const char* split_with, char* string,
                     int ignore_repeats) {
  if(string == NULL) return NULL;

  char** result = calloc(16, sizeof(char*));
  size_t i = 0;

  while(1) {
    result[i] = strsep(&string, split_with);

    if(result[i] == NULL) break;

    if(ignore_repeats) ignore_extra(split_with[0], &string);

    i += 1;
  }

  return result;
}
