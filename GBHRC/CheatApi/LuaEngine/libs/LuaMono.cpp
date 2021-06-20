#include "LuaMono.h"

#include <cassert>

#include "../../BrokeProtocol/Mono/dumper/MonoDumper.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

int LuaEngine::Libs::LuaMono::mono_dump(lua_State* state)
{
	assert(lua_isinteger(state, 1));
	
	Mono::Dumper::dump_object((Mono::MonoObject*)lua_tointeger(state,1));
	return 0;
}

LuaEngine::Libs::LuaMono::LuaMono(lua_State* state)
{
	lua_newtable(state);
	int indextab = lua_gettop(state);
	lua_pushvalue(state, indextab);
	lua_setglobal(state, "Mono");

	lua_pushcfunction(state, LuaMono::mono_dump);
	lua_setfield(state, -2, "dump");
}
