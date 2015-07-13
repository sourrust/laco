#include "util.h"

#include <stdio.h>

#include <lua.h>

#include "laco.h"

/* C Wrapper for lua's tostring function  */
inline static const char* to_lua_string(lua_State* L) {
  const char* result = NULL;

  lua_getglobal(L, "tostring");
  lua_insert(L, lua_gettop(L) - 1);

  if(lua_pcall(L, 1, 1, 0) == 0) {
    result = lua_tostring(L, -1);
  } else {
    lua_pop(L, 1);
  }

  return result;
}

/* Format printing of a single key value pair */
static void print_key_value(lua_State* L, char start_char) {
  printf("%c %s = %s\n",
      start_char, lua_tostring(L, -2),
      to_lua_string(L));
}

/* Format printing of a single list element */
static void print_list(lua_State* L, char start_char) {
  const char* format = NULL;
  if(start_char == '{') {
    format = "%c%s";
  } else {
    format = "%c %s";
  }
  printf(format, start_char, to_lua_string(L));
}


/* Print both types of tables */
static void print_table(lua_State* L) {
  bool first_elem = true;
  int luatype;

  lua_pushnil(L);

  /* check to see if table is empty */
  size_t table_size = lua_objlen(L, -2);
  int has_elements  = lua_next(L, -2);

  if(table_size == 0 && has_elements == 0) {
    printf("{ ");
  } else {
    do {
      luatype = lua_type(L, -2);

      /**
       * Check if the key it actually a string, because lua_isstring returns
       * true for numbers and we have a different printing for key value
       * tables and index value tables.
       */
      if(luatype == LUA_TSTRING) {
        print_key_value(L, (first_elem) ? '{' : ',');
        first_elem = false;
      } else {
        print_list(L, (first_elem) ? '{' : ',');
        first_elem = false;
      }
      lua_pop(L, 1);
    } while(lua_next(L, -2) != 0);
  }
  puts("}");
  lua_pop(L, 1);
}

/* External API */

int laco_print_type(LacoState* laco) {
  lua_State* L = laco_get_laco_lua_state(laco);
  int status   = laco_get_laco_status(laco);
  int luatype  = lua_type(L, -1);

  if(luatype != LUA_TTABLE) {
    lua_getglobal(L, "print");
    lua_insert(L, 1);

    status = lua_pcall(L, lua_gettop(L) - 1, 0, 0);
  } else {
    print_table(L);
  }

  laco_set_laco_status(laco, status);

  return status;
}

void laco_report_error(LacoState* laco, int status) {
  lua_State* L = laco_get_laco_lua_state(laco);

  if(status != 0 && lua_isstring(L, -1)) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    fflush(stderr);
    lua_pop(L, 1);
  }
}
