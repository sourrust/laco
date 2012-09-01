struct LacoState;

int laco_loadline(struct LacoState*);

void laco_handleline(struct LacoState*);

void laco_kill(struct LacoState*, int, const char*);
