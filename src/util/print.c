#include "print.h"

#include <stdio.h>
#include <stdbool.h>

#include <lua.h>

/* C Wrapper for lua's tostring function  */
inline static const char* toLuaString(lua_State* L) {
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
static void printKeyValue(lua_State* L, char startchar) {
  printf("%c %s = %s\n",
      startchar, lua_tostring(L, -2),
      toLuaString(L));
}

/* Format printing of a single list element */
static void printList(lua_State* L, char startchar) {
  printf("%c%s", startchar, toLuaString(L));
}


/* Print both types of tables */
static void printTable(lua_State* L) {
  bool firstelem = true;
  int luatype;

  lua_pushnil(L);
  while(lua_next(L, -2) != 0) {
    luatype = lua_type(L, -2);

    /**
     * Check if the key it actually a string, because lua_isstring returns
     * true for numbers and we have a different printing for key value
     * tables and index value tables.
     */
    if(luatype == LUA_TSTRING) {
      printKeyValue(L, (firstelem) ? '{' : ',');
      firstelem = false;
    } else {
      printList(L, (firstelem) ? '{' : ',');
      firstelem = false;
    }
    lua_pop(L, 1);
  }
  puts("}");
  lua_pop(L, 1);
}

/* External API*/

int laco_printtype(lua_State* L) {
  int status = 0;
  int luatype = lua_type(L, -1);

  if(luatype != LUA_TTABLE) {
    lua_getglobal(L, "print");
    lua_insert(L, 1);

    status = lua_pcall(L, lua_gettop(L) - 1, 0, 0);
  } else {
    printTable(L);
  }

  return status;
}

void laco_reportError(lua_State* L, int status) {
  if(status != 0 && lua_isstring(L, -1)) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    fflush(stderr);
    lua_pop(L, 1);
  }
}
