#include "laco.h"
#include "util.h"

int main(int argc, const char** argv) {
  struct LacoState* state = laco_newLacoState(argc, argv);

  while(laco_loadline(state) != -1) {
    laco_handleline(state);
  }

  laco_destroyLacoState(state);
  return 0;
}
