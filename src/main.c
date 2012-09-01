#include "laco.h"
#include "util.h"

int main(int argc, const char** argv) {
  struct LacoState* state = laco_newLacoState(argc, argv);
  struct lua_State* L = laco_getLuaState(state);

  while(laco_loadline(L) != -1) {
    laco_handleline(L);
  }

  laco_deleteLacoState(state);
  return 0;
}
