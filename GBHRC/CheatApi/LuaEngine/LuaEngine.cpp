#include "LuaEngine.h"

#include "../../includes/logger.h"
#include "../BrokeProtocol/BrokeProtocol.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int lua_exit(lua_State* L)
{
    if (lua_isstring(L, 1))
    {
        BrokeProtocol::show_local_message((char*)lua_tostring(L, 1));
    }

    return 0;
}

int lua_wait(lua_State* L)
{
    lua_Number number = lua_tonumber(L, 1);
    Sleep(number);
	
    return 0;
}


void add_globals(lua_State* state)
{
    luaL_openlibs(state);
    // register func
    lua_register(state, "print", lua_exit);
    //lua_register(L, "wait", lua_wait);
    // define globals
    lua_pushboolean(state, 1);
    lua_setglobal(state, "GBHRC");
}

void LuaEngine::execute(char* command)
{
    lua_State* L = luaL_newstate();
    add_globals(L);

    auto result = luaL_dostring(L, command);
	
    if (result != LUA_OK)
    {
        DEBUG_LOG("<LUA ERROR> " << lua_tostring(L, -1));
    }
}
