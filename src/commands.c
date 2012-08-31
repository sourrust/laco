#include "commands.h"

#include <stdio.h>
#include <string.h>

#include "lacoconf.h"
#include "util.h"

int isVersion(const char* arg) {
  int shorthand  = strcmp(arg, "-v");
  int normalhand = strcmp(arg, "--version");

  return shorthand || normalhand;
}

static void printVersion(struct lua_State* L) {
  printf("laco version %s\n", LACO_VERSION);
  laco_kill(L, 0, NULL);
}

void laco_handleFlag(struct lua_State* L, const char* arg) {
  if(arg == NULL) return;

  char argtype;
  if(isVersion(arg)) {
    argtype = 'v';
  }

  switch(argtype) {
    case 'v':
      printVersion(L);
    default:
      break;
  }
}
