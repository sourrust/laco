#ifndef LACO_FLAGS_H
#define LACO_FLAGS_H

struct LacoState;

/**
 * Takes the arguments inside of LacoState and executed any of flags
 * functionality when the arguments match.
 */
void laco_handle_flag(struct LacoState* laco);

#endif /* LACO_FLAGS_H */
