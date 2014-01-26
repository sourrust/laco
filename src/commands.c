#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "laco.h"
#include "util.h"

/* Check if the command flag is for version */
static int isVersion(const char* arg) {
  int shorthand  = strcmp(arg, "-v") == 0;
  int normalhand = strcmp(arg, "--version") == 0;

  return shorthand || normalhand;
}

/* Check if the command flag is for help */
static int isHelp(const char* arg) {
  int shorthand  = strcmp(arg, "-h") == 0
                || strcmp(arg, "-?") == 0;
  int normalhand = strcmp(arg, "--help") == 0;

  return shorthand || normalhand;
}

/* Print off the current version of laco */
static void printVersion(struct LacoState* laco) {
  const char* version = laco_getLacoVersion(laco);

  printf("laco version %s\n", version);
  laco_kill(laco, 0, NULL);
}

/* Print off the help screen */
static void printHelp(struct LacoState* laco) {
  puts("A better REPL for Lua.\n");
  puts("Usage: laco [options]\n");
  puts("-h | -? | --help   \tPrint this help screen");
  puts("-v | --version     \tPrint current version");

  laco_kill(laco, 0, NULL);
}

/* External API */

void laco_handleFlag(struct LacoState* laco) {
  const char* arg = laco_getLacoArgs(laco)[1];
  if(arg == NULL) return;

  char argtype;
  if(isVersion(arg)) {
    argtype = 'v';
  } else if(isHelp(arg)) {
    argtype = 'h';
  }

  switch(argtype) {
    case 'v':
      printVersion(laco);
    case 'h':
      printHelp(laco);
    default:
      break;
  }
}
