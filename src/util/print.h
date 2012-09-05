#ifndef __PRINT_H
#define __PRINT_H

struct lua_State;

/**
 * When there is a value on the lua stack, it will print out depending on
 * the type it is
 *
 * param          pointer to lua_State
 *
 * return LUA_ERRSYNTAX if the value has some error
 */
int laco_printtype(struct lua_State*);

#endif /* __PRINT_H */
