#pragma once

typedef struct lua_State lua_State;
namespace LuaEngine
{
	namespace Libs
	{
		class LuaMono
		{
		private:
			static int mono_dump(lua_State* state);
		public:
			LuaMono(lua_State*state);
		};
	}
}
