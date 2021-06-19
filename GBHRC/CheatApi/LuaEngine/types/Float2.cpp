#include "Float2.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

int LuaEngine::Float2::lua_float2_new(lua_State* state)
{
    lua_newtable(state);
    lua_pushnumber(state, lua_tonumber(state, 1));
    lua_setfield(state, -2, "x");
    lua_pushnumber(state, lua_tonumber(state, 2));
    lua_setfield(state, -2, "y");

    return 1;
}

DirectX::XMFLOAT2 LuaEngine::Float2::to_xmfloat2(lua_State* state, int index)
{
    float x, y;

    lua_getfield(state, index, "x");
    x = lua_tonumber(state, -1);
    lua_pop(state, 1);
    lua_getfield(state, index, "y");
    y = lua_tonumber(state, -1);
    lua_pop(state, 1);

    return { x, y };
}

LuaEngine::Float2::Float2(lua_State* state)
{
    lua_newtable(state);
    int indextab = lua_gettop(state);
    lua_pushvalue(state, indextab);
    lua_setglobal(state, "Float2");
    // instance function's
    lua_pushcfunction(state, lua_float2_new);
    lua_setfield(state, -2, "new");
}
