#ifndef __LACO_H
#define __LACO_H

struct lua_State;

/* State of laco REPL */
struct LacoState {
  struct lua_State* L;
  const char* version;

  int argc;
  const char** argv;

  int status;
};

/**
 * Initilazation of laco's state
 *
 * param          pointer to LacoState
 * param          argument count (argc)
 * param          arguments      (argv)
 */
void laco_initLacoState(struct LacoState*, int, const char**);

/**
 * Destroys the internal variable, but doesn't try to free the LacoState
 * pointer itself.
 *
 * param          pointer to LacoState
 *
 * return 1 if pointer isn't NULL
 */
int laco_destroyLacoState(struct LacoState*);

#endif /* __LACO_H */
