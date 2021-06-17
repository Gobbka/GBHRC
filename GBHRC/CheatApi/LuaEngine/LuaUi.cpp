#include "LuaUi.h"
#include "Form/Interactive/InteractiveForm.h"
#include "Form/Interactive/elements/Button/Button.h"
#include <map>
#include "LuaEngine.h"

using namespace Application;

extern Application::Render::Engine* pRenderEngine;
extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

struct CreateInstanceDesc;

typedef UI::InteractiveElement* (*CreateInstanceFunc)(CreateInstanceDesc*);

struct CreateInstanceDesc
{
    CreateInstanceFunc create_func;
    Render::Position pos;
    Render::Color color;
    Render::Resolution resolution;
    DirectX::SpriteFont* font;
    const char* text;
};


UI::InteractiveElement* CreateButton(CreateInstanceDesc* desc)
{
    return new UI::Button(desc->pos, desc->resolution, desc->color, desc->font, desc->text);
}

int LuaEngine::LuaUi::instance_new(lua_State* state)
{
    DEBUG_LOG("CREATE INSTANCE");
	if(lua_isstring(state,1))
	{
        lua_pushnil(state);
        return 1;
	}

    static std::map<const char*, CreateInstanceFunc>* name_func_map;
	if(name_func_map ==nullptr)
	{
        name_func_map = new std::map<const char*, CreateInstanceFunc>();
        (*name_func_map)["Button"] = CreateButton;
	}
	
    auto* instance_type = lua_tostring(state, 1);

    auto* create_func = (*name_func_map)[instance_type];
	if(!create_func)
	{
        lua_pushnil(state);
        return 1;
	}

    void* mem = lua_newuserdata(state, sizeof(CreateInstanceDesc));
    // todo: connect with meta table
	
    return 1;
}

int LuaEngine::LuaUi::gui_add_element(lua_State* state)
{
    DEBUG_LOG("ADDING ELEMENT");
    assert(lua_isuserdata(state, 1));
	
    return 1;
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
    lua_newtable(state);
    int indextab = lua_gettop(state);
    lua_pushvalue(state, indextab);
    lua_setglobal(state, "GUI");

    lua_pushcfunction(state, LuaUi::gui_new);
    lua_setfield(state, -2, "new");
    lua_pushcfunction(state, LuaUi::gui_add_element);
    lua_setfield(state, -2, "add_child");


    luaL_newmetatable(state, "GuiMetaTable");
    lua_pushstring(state, "__gc");
    lua_pushcfunction(state, LuaUi::gui_destroy);
    lua_settable(state, -3);
    lua_pushstring(state, "__index");
    lua_pushvalue(state, indextab);
    lua_settable(state, -3);

	// INSTANCE
    lua_newtable(state);
    indextab = lua_gettop(state);
    lua_pushvalue(state, indextab);
    lua_setglobal(state, "Instance");
    // instance function's
    lua_pushcfunction(state, LuaUi::instance_new);
    lua_setfield(state, -2, "new");
	
}
