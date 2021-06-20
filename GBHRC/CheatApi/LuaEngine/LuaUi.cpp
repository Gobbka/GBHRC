#include "LuaUi.h"
#include "Form/Interactive/InteractiveForm.h"
#include "Form/Interactive/elements/Button/Button.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include <map>
#include "LuaEngine.h"

using namespace Application;

extern Application::Render::Engine* pRenderEngine;
extern DirectX::SpriteFont* VisbyRoundCFFont;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

namespace LuaEngine
{
    struct LuaUIInstance
    {
        UI::InteractiveElement* element_ptr;
        Render::Position pos;
        Render::Color color;
        Render::Resolution resolution;
        DirectX::SpriteFont* font;
        const char* text;

    	void set_text(const char*text)
    	{ 	
    		if(this->element_ptr!=nullptr && this->element_ptr->get_desc().has_text)
    		{
                ((UI::Label*)this->element_ptr)->set_text(text);
    			// todo: complete
    		}else
    		{
                this->text = text;
    		}
    	}
    };

}

Application::UI::InteractiveElement* LuaEngine::InstanceFactory::create_button(LuaEngine::LuaUIInstance*instance)
{
    return new UI::Button(instance->pos, instance->resolution, instance->color, instance->font, instance->text);
}

Application::UI::InteractiveElement* LuaEngine::InstanceFactory::create_panel(LuaUIInstance* instance)
{
    return new UI::Panel(instance->pos, instance->resolution, instance->color);
}

bool LuaEngine::InstanceFactory::create_by_name(const char* name, LuaUIInstance* instance)
{
    // i try to make this using map, but map want index using strcmp
	
    if (strcmp(name, "Button") == 0)
    {
        instance->element_ptr = InstanceFactory::create_button(instance);
        return true;
    }

    if (strcmp(name, "Panel") == 0)
    {
        instance->element_ptr = InstanceFactory::create_panel(instance);
        return true;
    }
	
    return false;
}

int LuaEngine::LuaUi::instance_new(lua_State* state)
{
    DEBUG_LOG("CREATE INSTANCE");
    assert(lua_isstring(state, -1));
	
    const auto* instance_type = lua_tostring(state, 1);

    auto* mem = (LuaUIInstance*)lua_newuserdata(state, sizeof(LuaUIInstance));
    luaL_setmetatable(state, "InstanceMetaTable");

    mem->pos = { 0,0 };
    mem->resolution = { 300,300 };
    mem->color = { .4f,.4f,.4f,1.f };
    mem->text = "NULL";
    mem->font = VisbyRoundCFFont;
	
	if(!InstanceFactory::create_by_name(instance_type,mem))
	{
        DEBUG_LOG("PUSH NIL");
        lua_pushnil(state);
        return 1;
	}

	

    // ash.MouseButton1Down:Connect(function()
	

	
    return 1;
}

int LuaEngine::LuaUi::instance_destroy(lua_State* state)
{
    ((LuaUIInstance*)lua_touserdata(state, 1))->element_ptr->~InteractiveElement();
    return 0;
}

int LuaEngine::LuaUi::instance_index(lua_State* state)
{
    if(lua_isstring(state,2))
    {
        DEBUG_LOG("STRING");
        auto* field = lua_tostring(state, 2);
    	if(strcmp(field,"add_child")==0)
    	{
            lua_pushcfunction(state, LuaEngine::LuaUi::instance_add_child);
            return 1;
    	}
    }

    lua_pushnil(state);
    return 1;
}

int LuaEngine::LuaUi::instance_new_index(lua_State* state)
{
	
    assert(lua_isuserdata(state, -3)); // LuaUIInstance
    assert(lua_isstring(state, -2)); // field
	// -1 value

    auto* instance = (LuaUIInstance*)lua_touserdata(state, -3);
    auto* field = lua_tostring(state, -2);
	
	if(strcmp("Text",field)==0 && lua_isstring(state,-1))
	{
        instance->set_text(lua_tostring(state, -1));
        return 0;
	}

    if (strcmp("Visible", field) == 0 && lua_isboolean(state, -1))
    {
        instance->element_ptr->state.visible = (UI::VisibleState)lua_toboolean(state,-1);
        return 0;
    }

	if(strcmp("Parent",field)==0 && lua_isuserdata(state,-1))
	{
        assert(lua_isuserdata(state, -1));

        auto* parent = (LuaUIInstance*)lua_touserdata(state, -1);

        assert(instance->element_ptr);
        assert(parent->element_ptr);

        assert(instance->element_ptr != parent->element_ptr);
        assert(parent->element_ptr->get_desc().can_be_parent);

        ((UI::Parent*)parent->element_ptr)->add_element(instance->element_ptr);

        return 0;
	}

	if(strcmp("Color",field)==0 && lua_istable(state,-1))
	{
        instance->element_ptr->set_color((Render::Color)Color3::to_xmfloat3(state, -1));
        return 0;
	}

    if (strcmp("Size", field) == 0 && lua_istable(state, -1))
    {
        auto float2 = Float2::to_xmfloat2(state, -1);
        instance->element_ptr->set_resolution(float2.x,float2.y);
        return 0;
    }

	if(strcmp("Position",field)==0&&lua_istable(state,-1))
	{
        auto float2 = Float2::to_xmfloat2(state, -1);
        instance->element_ptr->set_pos(float2.x, float2.y);
        return 0;
	}
	
    return 0;
}

int LuaEngine::LuaUi::instance_add_child(lua_State* state)
{
    assert(lua_isuserdata(state, 1));
    assert(lua_isuserdata(state, 2));
	
    auto* new_child = (LuaUIInstance*)lua_touserdata(state, 2);
    auto* parent = (LuaUIInstance*)lua_touserdata(state, 1);

    assert(parent->element_ptr);
    assert(new_child->element_ptr);
	
    assert(parent->element_ptr != new_child->element_ptr);
    assert(parent->element_ptr->get_desc().can_be_parent);

    ((UI::Parent*)parent->element_ptr)->add_element(new_child->element_ptr);

    return 1;
}

int LuaEngine::LuaUi::gui_add_element(lua_State* state)
{
    DEBUG_LOG("ADDING ELEMENT");
    assert(lua_isuserdata(state, 2));
    assert(lua_isuserdata(state, 1));

    auto* form = (InteractiveForm*)lua_touserdata(state, 1);
    auto* gakba = (LuaUIInstance*)lua_touserdata(state, 2);

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
	:
	float3_table(state),
	float2_table(state)
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
