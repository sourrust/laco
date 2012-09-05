#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "laco.h"
#include "util.h"

typedef struct LacoState LacoState;

/* Check if the command flag is for version */
static int isVersion(const char* arg) {
  size_t size = strlen(arg);
  int shorthand  = memcmp(arg, "-v", size) == 0;
  int normalhand = memcmp(arg, "--version", size) == 0;

  return shorthand || normalhand;
}

/* Check if the command flag is for help */
static int isHelp(const char* arg) {
  size_t size = strlen(arg);
  int shorthand  = memcmp(arg, "-h", size) == 0
                || memcmp(arg, "-?", size) == 0;
  int normalhand = memcmp(arg, "--help", size) == 0;

  return shorthand || normalhand;
}

/* Print off the current version of laco */
static void printVersion(LacoState* state) {
  const char* version = state->version;

  printf("laco version %s\n", version);
  laco_kill(state, 0, NULL);
}

/* Print off the help screen */
static void printHelp(LacoState* state) {
  puts("A better REPL for Lua.\n");
  puts("Usage: laco [options]\n");
  puts("-h | -? | --help   \tPrint this help screen");
  puts("-v | --version     \tPrint current version");

  laco_kill(state, 0, NULL);
}

/* External API */

void laco_handleFlag(LacoState* state) {
  const char* arg = state->argv[1];
  if(arg == NULL) return;

  char argtype;
  if(isVersion(arg)) {
    argtype = 'v';
  } else if(isHelp(arg)) {
    argtype = 'h';
  }

  switch(argtype) {
    case 'v':
      printVersion(state);
    case 'h':
      printHelp(state);
    default:
      break;
  }
}
