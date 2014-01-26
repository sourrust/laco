#include "laco.h"
#include "util.h"

int main(int argc, const char** argv) {
  struct LacoState* laco = laco_newLacoState(argc, argv);

  while(laco_loadline(laco) != -1) {
    laco_handleline(laco);
  }

  laco_destroyLacoState(laco);
  return 0;
}
