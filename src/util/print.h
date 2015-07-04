#ifndef LACO_PRINT_H
#define LACO_PRINT_H

struct lua_State;

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

#endif /* LACO_PRINT_H */
