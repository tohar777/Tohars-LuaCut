#include "CLuaAPI.h"

namespace fs = std::filesystem;

int CLuaAPI::lc_messageBox(lua_State* L){
    const char* message = luaL_checkstring(L,1);
    MessageBoxA(nullptr,message,"LuaCut MessageBox",MB_OK);
    return 0;
}

int CLuaAPI::lc_cd(lua_State* L){
    std::error_code ec;
    const char* directory = luaL_checkstring(L,1);
    fs::current_path(directory,ec);
    if(ec){
        std::cerr << "[LCAPI] Failed to change to directory:" << directory << std::endl;
    }
    return 0;
}

int CLuaAPI::lc_mkdir(lua_State* L){

    std::error_code ec;
     const char* directory = luaL_checkstring(L,1);
    fs::create_directory(directory,ec);
    if(ec){
        std::cerr << "[LCAPI] Failed to create directory:" << directory << std::endl;
    }
    return 0;
}
int CLuaAPI::lc_list(lua_State* L)
{
    const char* directory = luaL_checkstring(L, 1);
    for (const auto& entry : fs::directory_iterator(directory)){
        std::cout << entry.path().filename().string() << "\n";
    }
    return 0;
}
void CLuaAPI::InitAPI(){

    L = luaL_newstate();

    luaopen_base(L);
    luaopen_table(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);

    /* LuaCut API */

    lua_pushcfunction(L, lc_messageBox);
    lua_setglobal(L, "lc_messageBox");

    lua_pushcfunction(L, lc_mkdir);
    lua_setglobal(L, "lc_mkdir");

    lua_pushcfunction(L, lc_cd);
    lua_setglobal(L, "lc_cd");

    lua_pushcfunction(L, lc_list);
    lua_setglobal(L, "lc_listDir");
}

void CLuaAPI::RunScript(const char* path){

    if(luaL_dofile(L, path) != LUA_OK)
    {
        printf("[CLAPI]Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}