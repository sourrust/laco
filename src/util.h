#ifndef LACO_UTIL_H
#define LACO_UTIL_H

struct LacoState;

/**
 * Load a line into the lua stack to evaluated later. This function will
 * return -1 if there is no line input to load.
 */
int laco_load_line(struct LacoState* laco);

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
 * returns 1 if true, and 0 if false.
 */
int laco_is_match(const char** matches, const char* test_string);

char** laco_line_to_words(char* line);

#endif /* LACO_UTIL_H */
