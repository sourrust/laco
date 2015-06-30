#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "laco.h"
#include "util.h"

/* Check if the command flag is for version */
static int is_version(const char* arg) {
  int short_hand  = strcmp(arg, "-v") == 0;
  int normal_hand = strcmp(arg, "--version") == 0;

  return short_hand || normal_hand;
}

/* Check if the command flag is for help */
static int is_help(const char* arg) {
  int short_hand  = strcmp(arg, "-h") == 0
                 || strcmp(arg, "-?") == 0;
  int normal_hand = strcmp(arg, "--help") == 0;

  return short_hand || normal_hand;
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
  const char* arg = laco_get_laco_args(laco)[1];
  if(arg == NULL) return;

  char arg_type;
  if(is_version(arg)) {
    arg_type = 'v';
  } else if(is_help(arg)) {
    arg_type = 'h';
  }

  switch(arg_type) {
    case 'v':
      print_version(laco);
    case 'h':
      print_help(laco);
    default:
      break;
  }
}
