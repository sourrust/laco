#include "util.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include "linenoise.h"
#include "commands.h"
#include "laco.h"

/* Check if line is incomplete */
static bool incomplete(lua_State* L, int status) {
  bool result = false;

  if(status == LUA_ERRSYNTAX) {
    size_t lmess;
    const char* mess = lua_tolstring(L, -1, &lmess);

    /* Check if the error ends in '<eof>' */
    size_t eof_size = sizeof(LUA_QL("<eof>")) - 1;
    const char* mess_end = mess + lmess - eof_size;
    if(strstr(mess, LUA_QL("<eof>")) == mess_end) {
      lua_pop(L, 1);
      result = true;
    }
  }

  return result;
}

/* Check if line can be printed */
static bool is_printable(lua_State* L, int status) {
  bool result = false;

  if(status == LUA_ERRSYNTAX) {
    const char* mess = lua_tostring(L, -1);

    bool is_literal  = strstr(mess,  "unexpected symbol") != NULL;
    bool is_variable = strstr(mess, "'=' expected") != NULL;

    if(is_literal || is_variable) {
      /* pop off error message */
      lua_pop(L, 1);

      const char* literal = lua_tostring(L, -1);
      lua_pop(L, 1);

      lua_pushfstring(L, "return %s", literal);

      result = true;
    }
  } else if(lua_type(L, -1) == LUA_TFUNCTION) {
    const char* func = lua_tostring(L, -2);

    /* check for a return statement */
    bool is_assignment = strstr(func, "=");

    if(!strstr(func, "return ") && !is_assignment) {
      lua_pop(L, 2);
      lua_pushfstring(L, "return %s", func);

      result = true;
    }
  }

  return result;
}

static char* get_line(LacoState* laco, const char* prompt) {
  char* line = linenoise(prompt);

  if(line != NULL) {
    linenoiseHistoryAdd(line);

    if(line[0] == ':') {
      laco_handle_command(laco, line);
    }
  }

  return line;
}

/* Push a line to the stack and store in history */
static bool pushline(LacoState* laco, bool isFirstLine) {
  const char* prompt = (isFirstLine) ? "> " : "... ";
  char* line         = get_line(laco, prompt);
  lua_State* L       = laco_get_laco_lua_state(laco);
  bool result        = false;

  if(line != NULL) {
    lua_pushstring(L, line);

    free(line);
    result = true;
  }

  return result;
}

/* External API */

int laco_load_line(LacoState* laco) {
  int status   = laco_get_laco_status(laco);
  lua_State* L = laco_get_laco_lua_state(laco);

  lua_settop(L, 0);

  if(!pushline(laco, true)) return -1;

  /* Until complete line */
  while(true) {
    status = luaL_loadbuffer(L, lua_tostring(L, 1), lua_strlen(L, 1),
                             "=stdin");

    if(is_printable(L, status)) continue;
    if(!incomplete(L, status)) break;
    if(!pushline(laco, false)) return -1;

    lua_pushliteral(L, "\n");
    lua_insert(L, -2);
    lua_concat(L, 3);
  }
  lua_remove(L, 1);
  laco_set_laco_status(laco, status);

  return status;
}

void laco_handle_line(LacoState* laco) {
  int status   = laco_get_laco_status(laco);
  lua_State* L = laco_get_laco_lua_state(laco);

  if(status == 0) {
    status = lua_pcall(L, 0, LUA_MULTRET, 0);
  }

  laco_report_error(laco, status);

  if(status == 0 && lua_gettop(L) > 0) {
    status = laco_print_type(laco);

    laco_report_error(laco, status);
  }

  laco_set_laco_status(laco, status);
}

void laco_kill(LacoState* laco, int status, const char* message) {
  laco_destroy_laco_state(laco);

  if(message != NULL) {
    fprintf(stderr, "%s\n", message);
  }

  exit(status);
}

int laco_is_match(const char** matches, const char* test_string) {
  int i;
  char* match;

  for(i = 0; (match = (char*) matches[i]); i++) {
    if(strcmp(test_string, match) == 0) {
      return true;
    }
  }

  return false;
}
