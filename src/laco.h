#ifndef LACO_H
#define LACO_H

struct lua_State;

/* State of laco REPL */
typedef struct LacoState LacoState;

/**
 * Allocates and initializes a new state for the laco REPL.
 */
LacoState* laco_new_laco_state(int argc, const char** argv);

/**
 * Cleans up all allocted data internally along with the pointer to laco
 * state. If the pointer isn't NULL, the function returns 1.
 */
int laco_destroy_laco_state(LacoState* laco);

/**
 * Gets the lua state held within laco.
 */
struct lua_State* laco_get_laco_lua_state(LacoState* laco);

/**
 * Gets the laco version held with laco. The format for the version is
 * `major.minor.patch`, essentually semver format.
 */
const char* laco_get_laco_version(LacoState* laco);

/**
 * Gets the arraying of arguments passed to the laco executable.
 */
const char** laco_get_laco_args(LacoState* laco);

/**
 * Gets the current status of the laco REPL.
 */
int laco_get_laco_status(LacoState* laco);

/**
 * Sets the current status of the laco REPL.
 */
void laco_set_laco_status(LacoState* laco, int status);

#endif /* LACO_H */
