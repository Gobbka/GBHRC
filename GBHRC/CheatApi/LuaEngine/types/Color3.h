#pragma once
#include <DirectXMath.h>

typedef struct lua_State lua_State;

namespace LuaEngine
{
	class Color3
	{
		static int lua_color3_new(lua_State* state);
	public:
		static DirectX::XMFLOAT3 to_xmfloat3(lua_State* state, int index);
		
		Color3(lua_State* state);
	};
}
