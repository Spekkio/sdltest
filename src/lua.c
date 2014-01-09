#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/*#include "config.h"*/

int load_config(char *filename)
{
  lua_State *L = luaL_newstate();

  luaopen_base(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);

  if(luaL_loadfile(L,filename) || lua_pcall(L,0,0,0)) {
    printf("cannot run lua script: %s\n",lua_tostring(L,-1));
    return 1;
  }

  lua_getglobal(L, "radius");
  lua_getglobal(L, "mousex_speed");
  lua_getglobal(L, "mousey_speed");
  lua_getglobal(L, "walk_speed");
  lua_getglobal(L, "rdelay");

  if(!lua_isnumber(L,-5))
    printf("`radius` should be a number\n");
  if(!lua_isnumber(L,-4))
    printf("`mousex_speed` should be a number\n");
  if(!lua_isnumber(L,-3))
    printf("`mousey_speed` should be a number\n");
  if(!lua_isnumber(L,-2))
    printf("`walk_speed` should be a number\n");
  if(!lua_isnumber(L,-1))
    printf("`rdelay` should be a number\n");

  /*
  *width = (int)lua_tonumber(L, -2);
  *height = (int)lua_tonumber(L, -1);
  */

  lua_close(L);
  return 0;
}
