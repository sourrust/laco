#ifndef __LACO_H
#define __LACO_H

struct LacoState;
struct lua_State;

struct LacoState* laco_newLacoState(int, const char**);
int laco_deleteLacoState(struct LacoState*);

struct lua_State* laco_getLuaState(struct LacoState*);
const char** laco_getArguments(struct LacoState*);
int laco_getArgumentCount(struct LacoState*);
const char* laco_getLacoVersion(struct LacoState*);
int laco_getCurrentStatus(struct LacoState*);

void laco_setCurrentStatus(struct LacoState*, int);

#endif /* __LACO_H */
