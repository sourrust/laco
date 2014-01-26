#ifndef __LACO_H
#define __LACO_H

struct lua_State;

/* State of laco REPL */
struct LacoState;

/**
 * Initilazation of laco's state
 *
 * param          pointer to LacoState
 * param          argument count (argc)
 * param          arguments      (argv)
 */
struct LacoState* laco_newLacoState(int, const char**);

/**
 * Destroys the internal variable, but doesn't try to free the LacoState
 * pointer itself.
 *
 * param          pointer to LacoState
 *
 * return 1 if pointer isn't NULL
 */
int laco_destroyLacoState(LacoState*);

#endif /* __LACO_H */
