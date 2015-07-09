#ifndef LACO_DEBUGGER_H
#define LACO_DEBUGGER_H

struct LacoState;

void laco_print_debug_info(struct LacoState* laco,
                           const char* function_name);

#endif /* LACO_DEBUGGER_H */
