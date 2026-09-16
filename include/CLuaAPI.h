#pragma once

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <windows.h>
}

#include <iostream>
#include <filesystem>
#include <imgui.h>

class CLuaAPI{
private:
    // general
    static int lc_messageBox(lua_State* L);
    // fs
    static int lc_cd(lua_State* L);
    static int lc_mkdir(lua_State* L);
    static int lc_list(lua_State* L);
    // logging
    static int lc_log(lua_State* L);
    static int lc_error(lua_State* L);
public:
    lua_State* L;

    bool scriptRunning = false;
    bool stopScript = false;

public:
    void InitAPI();
    void RunScript(const char* path);
    void RunString(const char* code);
    static void lc_hook(lua_State* L, lua_Debug* ar);
    void StopScript();
};