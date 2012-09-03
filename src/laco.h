#ifndef __LACO_H
#define __LACO_H

struct lua_State;

struct LacoState {
  struct lua_State* L;
  const char* version;

  int argc;
  const char** argv;

  int status;
};

void laco_initLacoState(struct LacoState*, int, const char**);
int laco_destroyLacoState(struct LacoState*);

#endif /* __LACO_H */
