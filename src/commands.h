#ifndef __COMMANDS_H
#define __COMMANDS_H

struct LacoState;

/**
 * Takes the arguments inside of LacoState and executed a flags
 * functionality
 *
 * param          pointer to LacoState
 */
void laco_handleFlag(struct LacoState*);

#endif /* __COMMANDS_H */
