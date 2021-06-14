#include "LuaEngine.h"

#include "../../includes/logger.h"
#include "../BrokeProtocol/BrokeProtocol.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

LuaEngine::Context* LuaEngineContext;

int lua_sendMessage(lua_State* L)
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
    lua_register(state, "sendMessage", lua_sendMessage);
    lua_register(state, "wait", lua_wait);
    // define globals
    lua_pushboolean(state, 1);
    lua_setglobal(state, "GBHRC");
}

LuaEngine::LuaExecution::LuaExecution(lua_State* state)
{
    this->state = state;
}

void LuaEngine::LuaExecution::dostring(char* command)
{
    auto result = luaL_dostring(state, command);

    if (result != LUA_OK)
    {
        DEBUG_LOG("<LUA ERROR> " << lua_tostring(this->state, -1));
    }
}

bool LuaEngine::LuaExecution::is_events_subscribed()
{
    return this->events_subscribed;
}

LuaEngine::LuaExecution::~LuaExecution()
{
    lua_close(state);
}

void LuaEngine::Context::execute(char* command)
{
    if (LuaEngineContext==nullptr)
        LuaEngineContext = new LuaEngine::Context();
	
    lua_State* L = luaL_newstate();
    add_globals(L);

    auto* lua_exec = new LuaExecution(L);
    lua_exec->dostring(command);
	if(lua_exec->is_events_subscribed())
	{
        LuaEngineContext->lua_list.push_back(lua_exec);
	}else
	{
        delete lua_exec;
	}

}

