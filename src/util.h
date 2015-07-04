#ifndef LACO_UTIL_H
#define LACO_UTIL_H

struct LacoState;
struct lua_State;

/**
 * Load a line into the lua stack to be evaluated later
 *
 * param          pointer to LacoState
 *
 * return -1 if there is no line input to load
 */
int laco_load_line(struct LacoState* laco);

/**
 * Called after laco_load_line, this evaluated the line as a function and
 * hands of the result for printing
 *
 * param          pointer to LacoState
 */
void laco_handle_line(struct LacoState* laco);

/**
 * Kills the loop with exiting message if specified
 *
 * param          pointer to LacoState
 * param          exit with status
 * param          error message
 */
void laco_kill(struct LacoState* laco, int status, const char* message);

/**
 * When there is a value on the lua stack, it will print out depending on
 * the type it is
 *
 * param          pointer to lua_State
 *
 * return LUA_ERRSYNTAX if the value has some error
 */
int laco_print_type(struct lua_State* L);


/**
 * Prints out and pops off errors pushed into the lua stack
 *
 * param          pointer to lua_State
 * param          incoming lua stack status
 */
void laco_report_error(struct lua_State* L, int status);

int laco_is_match(const char** matches, const char* test_string);

#endif /* LACO_UTIL_H */
