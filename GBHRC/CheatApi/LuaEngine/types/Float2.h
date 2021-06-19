#pragma once
#include <DirectXMath.h>

typedef struct lua_State lua_State;

namespace LuaEngine
{
	class Float2
	{
		static int lua_float2_new(lua_State* state);
	public:
		static DirectX::XMFLOAT2 to_xmfloat2(lua_State* state, int index);

		Float2(lua_State* state);
	};
}
