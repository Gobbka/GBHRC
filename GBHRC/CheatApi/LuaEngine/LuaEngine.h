#pragma once
#include "LuaUi.h"
#include <vector>

#include "libs/LuaMono.h"

namespace LuaEngine
{

	class LuaExecution
	{
		LuaUi luaUi;
		Libs::LuaMono lua_mono;

		lua_State* state;
		bool events_subscribed = false;
	public:
		lua_State* get_state();
		
		LuaExecution(lua_State*state);
		void dostring(char* command);
		bool can_close();

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

