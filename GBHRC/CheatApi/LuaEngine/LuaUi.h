#pragma once


namespace Application {
	namespace UI {
		class InteractiveElement;
	}
}

typedef struct lua_State lua_State;
namespace LuaEngine
{
	struct LuaUIInstance;
	
	class InstanceFactory
	{
		static Application::UI::InteractiveElement* create_button(LuaUIInstance*instance);
		static Application::UI::InteractiveElement* create_panel(LuaUIInstance*instance);
	public:

		static bool create_by_name(const char* name,LuaUIInstance*instance);
	};

	class LuaUi
	{
	private:
		static int instance_new(lua_State* state);
		static int instance_destroy(lua_State* state);
		static int instance_index(lua_State* state);
		static int instance_new_index(lua_State* state);
		static int instance_add_child(lua_State* state);
		
		static int gui_add_element(lua_State*state);
		static int gui_new(lua_State* state);
		static int gui_destroy(lua_State* state);
	public:
		LuaUi(lua_State* state);

	};

}
