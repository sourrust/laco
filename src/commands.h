#ifndef LACO_COMMANDS_H
#define LACO_COMMANDS_H

struct LacoState;

/**
 * Gets passed ever line to see if it matches one of the REPL command. If it
 * does, that command will be executed.
 */
void laco_handle_command(struct LacoState* laco, char* line);

#endif /* LACO_COMMANDS_H */
