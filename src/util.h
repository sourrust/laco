struct lua_State;

int laco_loadline(struct lua_State*);

void laco_handleline(struct lua_State*);

void laco_kill(struct lua_State*, int, const char*);
