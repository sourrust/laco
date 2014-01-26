#ifndef __LACO_H
#define __LACO_H

struct lua_State;

/* State of laco REPL */
struct LacoState;

/**
 * Makes a new LacoState.
 *
 * param          argument count (argc)
 * param          arguments      (argv)
 *
 * return a pointer to new LacoState.
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
int laco_destroyLacoState(struct LacoState*);

/**
 * Gets the lua state held with laco.
 *
 * param          pointer to LacoState
 *
 * return a pointer to lua_State
 */
struct lua_State* laco_getLacoLuaState(struct LacoState*);

/**
 * Gets the laco version held with laco.
 *
 * param          pointer to LacoState
 *
 * return a string of characters representing laco's version number
 */
const char* laco_getLacoVersion(struct LacoState*);

/**
 * Gets the arraying of arguments passed to laco.
 *
 * param          pointer to LacoState
 *
 * return an array of characters string passes into laco
 */
const char** laco_getLacoArgs(struct LacoState*);

/**
 * Get the current status of the laco repl.
 *
 * param          pointer to LacoState
 *
 * return the current status of laco
 */
int laco_getLacoStatus(struct LacoState*);

/**
 * Set the current status of laco.
 *
 * param          pointer to LacoState
 * param          status to be set
 */
void laco_setLacoStatus(struct LacoState*, int);

#endif /* __LACO_H */
