#ifndef LACO_UTIL_H
#define LACO_UTIL_H

#include <stdbool.h>
#include <assert.h>

struct LacoState;

/**
 * Generalized function pointer for handling commands from from either a
 * command line flag or a command inside of laco itself.
 */
typedef void (*LacoHandler)(struct LacoState* laco, const char** arguments);

/**
 * A representation of each command with a list of string matches and a
 * function pointer to the behavior of said command. When there is a match
 * to one of the string, this function will be called and passed in the
 * appropriate arguments.
 */
struct LacoCommand {
  const char** matches;
  LacoHandler handler;
};
typedef struct LacoCommand LacoCommand;

/**
 * Load a line into the lua stack to evaluated later. This function will
 * return false if there is no line input to load.
 */
bool laco_load_line(struct LacoState* laco);

/**
 * Called after laco_load_line, this will evaluate the line as a function
 * and hands off the result for printing.
 */
void laco_handle_line(struct LacoState* laco);

/**
 * Kills the loop with exiting message if specified.
 */
void laco_kill(struct LacoState* laco, int status, const char* message);

/**
 * When there is a value on the lua stack, this will print out the current
 * type it is. When an error acquires, laco_print_type will return
 * LUA_ERRSYNTAX.
 */
int laco_print_type(struct LacoState* laco);

/**
 * Prints out and pops off errors pushed into the lua stack.
 */
void laco_report_error(struct LacoState* laco, int status);

/**
 * Checks if the test string matches any of the string in matches and
 * returns true with a match, and false without any matches.
 */
bool laco_is_match(const char** matches, const char* test_string);

/**
 * Break the provided string into an array of strings that are between the
 * split_with value. The last value of this array will be NULL.
 */
char** laco_split_by(const char split_with, char* string,
                     int ignore_repeats);

/* Macro for splitting with spaces */
#define laco_line_to_words(line) \
  laco_split_by(' ', line, 1)

/**
 * Goes through each instance from the list of commands and see if there is
 * a match with for command_keyword. When there is a match, the defined
 * handler inside the LacoCommand gets called -- passing in LacoState and
 * the arguments. The list of commands expects the last entry of the array
 * to be `{ NULL, NULL }` for ease of iteration.
 */
void laco_dispatch(const LacoCommand* commands, struct LacoState* laco,
                   const char* command_keyword, const char** arguments);

#endif /* LACO_UTIL_H */
