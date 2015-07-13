#ifndef LACO_COMMANDS_H
#define LACO_COMMANDS_H

struct LacoState;

typedef void (*LacoHandler)(struct LacoState* laco, const char** arguments);

struct LacoCommand {
  const char** matches;
  LacoHandler handler;
};

/**
 * Goes through each instance from the list of commands and see if there is
 * a match with for command_keyword. When there is a match, the defined
 * handler inside the LacoCommand gets called -- passing in LacoState and
 * the arguments. The list of commands expects the last entry of the array
 * to be `{ NULL, NULL }` for ease of iteration.
 */
void laco_dispatch(const struct LacoCommand* commands,
                   struct LacoState* laco, const char* command_keyword,
                   const char** arguments);

/**
 * Gets passed ever line to see if it matches one of the REPL command. If it
 * does, that command will be executed.
 */
void laco_handle_command(struct LacoState* laco, char* line);

#endif /* LACO_COMMANDS_H */
