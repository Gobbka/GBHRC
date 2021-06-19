#include "Color3.h"


#include <cstring>
#include <DirectXMath.h>
#include <new>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}


int LuaEngine::Color3::lua_color3_new(lua_State* state)
{
    lua_newtable(state);
	lua_pushnumber(state, lua_tonumber(state, 1)/255);
    lua_setfield(state, -2, "r");
    lua_pushnumber(state, lua_tonumber(state, 2)/255);
    lua_setfield(state, -2, "g");
    lua_pushnumber(state, lua_tonumber(state, 3)/255);
    lua_setfield(state, -2, "b");
	
    return 1;
}

DirectX::XMFLOAT3 LuaEngine::Color3::to_xmfloat3(lua_State* state, int index)
{
    float x, y, z;
	
    lua_getfield(state, index, "r");
    x = lua_tonumber(state, -1);
    lua_pop(state, 1);
    lua_getfield(state, index, "g");
    y = lua_tonumber(state, -1);
    lua_pop(state, 1);
    lua_getfield(state, index, "b");
    z = lua_tonumber(state, -1);
    lua_pop(state, 1);

    return {x, y, z};
}

LuaEngine::Color3::Color3(lua_State* state)
{
    // COLOR
    lua_newtable(state);
    int indextab = lua_gettop(state);
    lua_pushvalue(state, indextab);
    lua_setglobal(state, "Color3");
    // instance function's
    lua_pushcfunction(state, Color3::lua_color3_new);
    lua_setfield(state, -2, "new");
}
