#include "CLuaAPI.h"

namespace fs = std::filesystem;

int CLuaAPI::lc_messageBox(lua_State* L){
    const char* message = luaL_checkstring(L,1);
    const char* type = luaL_checkstring(L,2);
    if(strcmp(type,"info")==0){
        MessageBoxA(nullptr,message,"LuaCut MessageBox",MB_ICONINFORMATION | MB_OK);
    }
    if(strcmp(type,"warn")==0){
        MessageBoxA(nullptr,message,"LuaCut MessageBox",MB_ICONWARNING | MB_OK);
    }
    if(strcmp(type,"error")==0){
        MessageBoxA(nullptr,message,"LuaCut MessageBox",MB_ICONERROR | MB_OK);
    }
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
int CLuaAPI::lc_log(lua_State* L){
    const char* text = luaL_checkstring(L,1);
    printf("[LCAPI-LOG]%s \n",text);
    return 0;
}
int CLuaAPI::lc_error(lua_State* L){
    const char* text = luaL_checkstring(L,1);
    printf("[LCAPI-ERROR]%s \n",text);
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

    luaL_openlibs(L);

    /* LuaCut API */

    lua_pushcfunction(L, lc_messageBox);
    lua_setglobal(L, "lc_messageBox");

    lua_pushcfunction(L, lc_mkdir);
    lua_setglobal(L, "lc_mkdir");

    lua_pushcfunction(L, lc_cd);
    lua_setglobal(L, "lc_cd");

    lua_pushcfunction(L, lc_list);
    lua_setglobal(L, "lc_listDir");

    lua_pushcfunction(L, lc_log);
    lua_setglobal(L, "lc_log");

    lua_pushcfunction(L, lc_error);
    lua_setglobal(L, "lc_error");
}

void CLuaAPI::RunScript(const char* path){

    if(luaL_dofile(L, path) != LUA_OK)
    {
        printf("[CLAPI]Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}
void CLuaAPI::RunString(const char* code){

    if(luaL_dostring(L, code) != LUA_OK)
    {
        printf("[CLAPI]Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}
void CLuaAPI::StopScript(){

}