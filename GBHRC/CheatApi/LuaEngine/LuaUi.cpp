#include "LuaUi.h"
#include "Form/Interactive/InteractiveForm.h"
#include "LuaEngine.h"

extern Application::Render::Engine* pRenderEngine;
extern "C" {
#include <lua.h>
#include <lauxlib.h>
}


int LuaEngine::LuaUi::gui_new(lua_State* state)
{
    DEBUG_LOG("MAKING GUI...");
    auto* ptr= lua_newuserdata(state, sizeof(Application::InteractiveForm));

    new (ptr) Application::InteractiveForm(pRenderEngine);
    Application::Context::register_form((Application::InteractiveForm*)ptr);

    luaL_getmetatable(state, "GuiMetaTable");
	
    lua_setmetatable(state, -2);
	
    return 1;
}

int LuaEngine::LuaUi::gui_destroy(lua_State* state)
{
    auto* form = (Application::InteractiveForm*)lua_touserdata(state, -1);
    form->~InteractiveForm();
    Application::Context::remove_form(form);
	
    return 0;
}

LuaEngine::LuaUi::LuaUi(lua_State*state)
{

    luaL_newmetatable(state, "GuiMetaTable");
    lua_pushstring(state, "__gc");
    lua_pushcfunction(state, LuaUi::gui_destroy);
    lua_settable(state, -3);
	
    lua_newtable(state);
    int indextab = lua_gettop(state);
    lua_pushvalue(state, indextab);
    lua_setglobal(state, "GUI");

    lua_pushcfunction(state, LuaUi::gui_new);
    lua_setfield(state, -2, "new");
}
