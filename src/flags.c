#include "flags.h"

#include <stdio.h>

#include "laco.h"
#include "util.h"

enum LacoFlags {
  LACO_HELP,
  LACO_VERSION
};

static const char* version_matches[] = {"-v", "--version", NULL};
static const char* help_matches[]    = {"-h", "-?", "--help", NULL};

/* Check if the command flag is for version */
static inline bool is_version(const char* arg) {
  return laco_is_match(version_matches, arg);
}

/* Check if the command flag is for help */
static inline bool is_help(const char* arg) {
  return laco_is_match(help_matches, arg);
}

/* Print off the current version of laco */
static void print_version(LacoState* laco) {
  const char* version = laco_get_laco_version(laco);

  printf("laco version %s\n", version);
  laco_kill(laco, 0, NULL);
}

/* Print off the help screen */
static void print_help(LacoState* laco) {
  puts("A better REPL for Lua.\n");
  puts("Usage: laco [options]\n");
  puts("-h | -? | --help   \tPrint this help screen");
  puts("-v | --version     \tPrint current version");

  laco_kill(laco, 0, NULL);
}

/* External API */

void laco_handle_flag(LacoState* laco) {
  int arg_type;
  const char* arg = laco_get_laco_args(laco)[1];
  if(arg == NULL) return;

  if(is_version(arg)) {
    arg_type = LACO_VERSION;
  } else if(is_help(arg)) {
    arg_type = LACO_HELP;
  }

  switch(arg_type) {
    case LACO_VERSION:
      print_version(laco);
    case LACO_HELP:
      print_help(laco);
    default:
      break;
  }
}
