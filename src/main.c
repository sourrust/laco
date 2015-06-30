#include "laco.h"
#include "util.h"

int main(int argc, const char** argv) {
  LacoState* laco = laco_new_laco_state(argc, argv);

  while(laco_load_line(laco) != -1) {
    laco_handle_line(laco);
  }

  laco_destroy_laco_state(laco);
  return 0;
}
