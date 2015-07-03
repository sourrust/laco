#ifndef __UTIL_H
#define __UTIL_H

struct LacoState;

/**
 * Load a line into the lua stack to be evaluated later
 *
 * param          pointer to LacoState
 *
 * return -1 if there is no line input to load
 */
int laco_load_line(struct LacoState* laco);

/**
 * Called after laco_load_line, this evaluated the line as a function and
 * hands of the result for printing
 *
 * param          pointer to LacoState
 */
void laco_handle_line(struct LacoState* laco);

/**
 * Kills the loop with exiting message if specified
 *
 * param          pointer to LacoState
 * param          exit with status
 * param          error message
 */
void laco_kill(struct LacoState* laco, int status, const char* message);

int laco_is_match(const char** matches, const char* test_string);

#endif /* __UTIL_H */
