#include "LuaUi.h"
#include "Form/Interactive/InteractiveForm.h"
#include "Form/Interactive/elements/Button/Button.h"
#include <map>
#include "LuaEngine.h"

using namespace Application;

extern Application::Render::Engine* pRenderEngine;
extern DirectX::SpriteFont* VisbyRoundCFFont;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

struct LuaUIInstance;

typedef UI::InteractiveElement* (*CreateInstanceFunc)(LuaUIInstance*);

struct LuaUIInstance
{
    UI::InteractiveElement* element_ptr;
    CreateInstanceFunc create_func;
    Render::Position pos;
    Render::Color color;
    Render::Resolution resolution;
    DirectX::SpriteFont* font;
    const char* text;

	UI::InteractiveElement* create()
	{
        return this->create_func(this);
	}
};


UI::InteractiveElement* CreateButton(LuaUIInstance* desc)
{
    return new UI::Button(desc->pos, desc->resolution, desc->color, desc->font, desc->text);
}

int LuaEngine::LuaUi::instance_new(lua_State* state)
{
    DEBUG_LOG("CREATE INSTANCE");
    assert(lua_isstring(state, -1));
    CreateInstanceFunc create_func=nullptr;
	
    const auto* instance_type = lua_tostring(state, 1);

    if (strcmp(instance_type, "Button") == 0)
        create_func = CreateButton;
    
	if(!create_func)
	{
        DEBUG_LOG("PUSH NIL");
        lua_pushnil(state);
        return 1;
	}

    auto* mem = (LuaUIInstance*)lua_newuserdata(state, sizeof(LuaUIInstance));
    luaL_setmetatable(state,"InstanceMetaTable");

    mem->pos = { 0,0 };
    mem->resolution = { 300,300 };
    mem->color = { .4f,.4f,.4f,1.f };
    mem->text = "NULL";
    mem->create_func = create_func;
    mem->font = VisbyRoundCFFont;
	
	
    return 1;
}

int LuaEngine::LuaUi::instance_destroy(lua_State* state)
{
    ((LuaUIInstance*)lua_touserdata(state, 1))->element_ptr->~InteractiveElement();
    return 0;
}

int LuaEngine::LuaUi::instance_index(lua_State* state)
{
    lua_pushnumber(state, 228);
    return 1;
}

int LuaEngine::LuaUi::instance_new_index(lua_State* state)
{
    assert(lua_isuserdata(state, -3)); // LuaUIInstance
    assert(lua_isstring(state, -2)); // field
	
	
    return 0;
}

int LuaEngine::LuaUi::gui_add_element(lua_State* state)
{
    DEBUG_LOG("ADDING ELEMENT");
    assert(lua_isuserdata(state, 2));
    assert(lua_isuserdata(state, 1));

    auto* form = (InteractiveForm*)lua_touserdata(state, 1);
    auto* gakba = (LuaUIInstance*)lua_touserdata(state, 2);
    gakba->element_ptr = gakba->create();

    form->add_element(gakba->element_ptr);
	
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

    luaL_newmetatable(state, "InstanceMetaTable");
    lua_pushstring(state, "__gc");
    lua_pushcfunction(state, LuaUi::instance_destroy);
    lua_settable(state, -3);
    lua_pushstring(state, "__index");
    lua_pushcfunction(state, LuaUi::instance_index);
    lua_settable(state, -3);
    lua_pushstring(state, "__newindex");
    lua_pushcfunction(state, LuaUi::instance_new_index);
    lua_settable(state, -3);
}
