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

struct lua_State* laco_getLacoLuaState(struct LacoState*);

const char* laco_getLacoVersion(struct LacoState*);

const char** laco_getLacoArgs(struct LacoState*);

int laco_getLacoStatus(struct LacoState*);
void laco_setLacoStatus(struct LacoState*, int);

#endif /* __LACO_H */
