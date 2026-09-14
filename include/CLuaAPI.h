#pragma once
extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
class CLuaAPI{
    private:
        void lc_messageBox();
    public:
        lua_State* L;
    public:
        void InitAPI();
        void RunScript(const char* path);
};