#ifndef __FLAGS_H
#define __FLAGS_H

struct LacoState;

/**
 * Takes the arguments inside of LacoState and executed a flags
 * functionality
 *
 * param          pointer to LacoState
 */
void laco_handle_flag(struct LacoState* laco);

#endif /* __FLAGS_H */
