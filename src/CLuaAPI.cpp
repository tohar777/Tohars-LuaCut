#include "CLuaAPI.h"

void CLuaAPI::InitAPI(){
    L = luaL_newstate();
    luaopen_base(L);   /* opens the basic library */
    luaopen_table(L);  /* opens the table library */
    luaopen_io(L);     /* opens the I/O library */
    luaopen_string(L); /* opens the string lib. */
    luaopen_math(L);   /* opens the math lib. */
}
void CLuaAPI::RunScript(const char* path){
    if(luaL_dofile(L, path) != LUA_OK)
    {
        printf("[LCAPI]Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}