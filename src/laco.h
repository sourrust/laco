struct LacoState;
struct lua_State;

struct LacoState* laco_newLacoState(int, const char**);
int laco_deleteLacoState(struct LacoState*);

struct lua_State* laco_getLuaState(struct LacoState*);
