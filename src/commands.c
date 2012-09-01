#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "laco.h"
#include "lacoconf.h"
#include "util.h"

typedef struct LacoState LacoState;

static int isVersion(const char* arg) {
  size_t size = strlen(arg);
  int shorthand  = memcmp(arg, "-v", size) == 0;
  int normalhand = memcmp(arg, "--version", size) == 0;

  return shorthand || normalhand;
}

static int isHelp(const char* arg) {
  size_t size = strlen(arg);
  int shorthand  = memcmp(arg, "-h", size) == 0
                || memcmp(arg, "-?", size) == 0;
  int normalhand = memcmp(arg, "--help", size) == 0;

  return shorthand || normalhand;
}

static void printVersion(LacoState* state) {
  printf("laco version %s\n", LACO_VERSION);
  laco_kill(state, 0, NULL);
}

static void printHelp(LacoState* state) {
  puts("A better REPL for Lua.\n");
  puts("Usage: laco [options]\n");
  puts("-h | -? | --help   \tPrint this help screen");
  puts("-v | --version     \tPrint current version");

  laco_kill(state, 0, NULL);
}

void laco_handleFlag(LacoState* state, const char* arg) {
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
