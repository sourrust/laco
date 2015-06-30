#ifndef __LACO_H
#define __LACO_H

struct lua_State;

/* State of laco REPL */
typedef struct LacoState LacoState;

/**
 * Makes a new LacoState.
 *
 * param          argument count
 * param          arguments
 *
 * return a pointer to new LacoState.
 */
LacoState* laco_new_laco_state(int argc, const char** argv);

/**
 * Destroys the internal variable, but doesn't try to free the LacoState
 * pointer itself.
 *
 * param          pointer to LacoState
 *
 * return 1 if pointer isn't NULL
 */
int laco_destroy_laco_state(LacoState* laco);

/**
 * Gets the lua state held with laco.
 *
 * param          pointer to LacoState
 *
 * return a pointer to lua_State
 */
struct lua_State* laco_get_laco_lua_state(LacoState* laco);

/**
 * Gets the laco version held with laco.
 *
 * param          pointer to LacoState
 *
 * return a string of characters representing laco's version number
 */
const char* laco_get_laco_version(LacoState* laco);

/**
 * Gets the arraying of arguments passed to laco.
 *
 * param          pointer to LacoState
 *
 * return an array of characters string passes into laco
 */
const char** laco_get_laco_args(LacoState* laco);

/**
 * Get the current status of the laco repl.
 *
 * param          pointer to LacoState
 *
 * return the current status of laco
 */
int laco_get_laco_status(LacoState* laco);

/**
 * Set the current status of laco.
 *
 * param          pointer to LacoState
 * param          status to be set
 */
void laco_set_laco_status(LacoState* laco, int status);

#endif /* __LACO_H */
