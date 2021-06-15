#include "LuaEngine.h"

#include "../../includes/logger.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "Form/Interactive/elements/IElement/InteractiveElement.h"
#include "Form/Interactive/elements/Panel/Panel.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

LuaEngine::Context* LuaEngineContext;

int lua_showMessage(lua_State* L)
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

int lua_messagebox(lua_State* L)
{
    MessageBoxA(0, lua_tostring(L, 1), "GBHRC", MB_OK);

    return 0;
}

int lua_get_player(lua_State*L)
{
	if(lua_isstring(L,2) && strcmp("local_player",lua_tostring(L,2))==0)
	{
        lua_pushinteger(L, (lua_Integer)BrokeProtocol::GetLocalPlayer());
        return 1;
	}

    if (lua_isstring(L, 2) && strcmp("length", lua_tostring(L, 2)) == 0)
    {
        lua_pushnumber(L, (lua_Number)BrokeProtocol::GetPlayersCollection()->items->size());
        return 1;
    }

	if(lua_isnumber(L,2))
		lua_pushinteger(L, (lua_Integer)BrokeProtocol::GetPlayersCollection()->items->pointer()[lua_tointeger(L,2)]);
	
    DEBUG_LOG("GET_PLAYER");
    return 1;
}

int lua_get_players(lua_State*L)
{
    luaL_newmetatable(L, "PlayerCollectionMetaTable");
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, lua_get_player);
    lua_settable(L, -3);

	
    lua_newtable(L);
    luaL_getmetatable(L, "PlayerCollectionMetaTable");

    lua_setmetatable(L, -2);

    return 1;
}

int lua_workspace__index(lua_State*L)
{

    if (lua_isstring(L, 2) && strcmp("players", lua_tostring(L, 2)) == 0)
    {
        return lua_get_players(L);
    }

    lua_pushnil(L);
    return 1;
}

int lua_ui_new(lua_State*L)
{
	
    Application::UI::InteractiveElementDesc* desc = (Application::UI::InteractiveElementDesc*)lua_newuserdata(L, sizeof(Application::UI::InteractiveElementDesc));
    new (desc) Application::UI::InteractiveElementDesc;

	if(lua_isstring(L,1) && strcmp("Panel",lua_tostring(L,1)) == 0)
	{
        desc->create_func = Application::UI::Panel::create;
	}

    lua_pushinteger(L, (lua_Integer)desc);
    return 1;
}

int lua_getworkspace_metatable(lua_State*L)
{
    luaL_newmetatable(L, "WorkSpaceMetaTable");
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, lua_workspace__index);
    lua_settable(L, -3);


    lua_newtable(L);
    luaL_getmetatable(L, "WorkSpaceMetaTable");

    lua_setmetatable(L, -2);
	
    return 1;
}

void add_globals(lua_State* state)
{
    luaL_openlibs(state);
    // register func
    lua_register(state, "showMessage", lua_showMessage);
    lua_register(state, "wait", lua_wait);
    lua_register(state, "messageBox", lua_messagebox);
    lua_register(state, "getPlayers", lua_get_players);
    // define globals
    lua_pushboolean(state, 1);
    lua_setglobal(state, "GBHRC");
    lua_getworkspace_metatable(state);
    lua_setglobal(state, "workspace");


}

lua_State* LuaEngine::LuaExecution::get_state()
{
    return this->state;
}

LuaEngine::LuaExecution::LuaExecution(lua_State* state)
	:
luaUi(state)
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

