#pragma once
#include "LuaUi.h"
#include <vector>
typedef struct lua_State lua_State;
namespace LuaEngine
{

	class LuaExecution
	{
		LuaUi luaUi;
		lua_State* state;
		bool events_subscribed = false;
	public:
		lua_State* get_state();
		
		LuaExecution(lua_State*state);
		void dostring(char* command);
		bool is_events_subscribed();

		~LuaExecution();
	};
	
	class Context final
	{
	private:
		std::vector<LuaExecution*> lua_list;
	public:
		static void execute(char* command);
	};

}

