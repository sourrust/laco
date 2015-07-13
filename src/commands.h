#ifndef LACO_COMMANDS_H
#define LACO_COMMANDS_H

struct LacoState;

typedef void (*LacoHandler)(struct LacoState* laco, const char** arguments);

struct LacoCommand {
  const char** matches;
  LacoHandler handler;
};

void laco_dispatch(const struct LacoCommand* commands,
                   struct LacoState* laco, const char* command_keyword,
                   const char** arguments);

/**
 * Gets passed ever line to see if it matches one of the REPL command. If it
 * does, that command will be executed.
 */
void laco_handle_command(struct LacoState* laco, char* line);

#endif /* LACO_COMMANDS_H */
