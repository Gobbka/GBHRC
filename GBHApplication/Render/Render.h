#pragma once
#include "../../GBHRC/includes/d3d.h"
#include "../../GBHRC/includes/logger.h"
#include "../../GBHRC/includes/win.h"
#include "Events/EngineEvents.h"

namespace Application
{
	namespace Render
	{
		struct Color3
		{
			float r; float g; float b;
			Color3(float r, float g, float b) : r(r), g(g), b(b) {};
			Color3(float r, float g, float b, float a) : r(r), g(g), b(b) {};
			Color3(DirectX::XMFLOAT3 f3) : r(f3.x), g(f3.y), b(f3.z) {};
		};
		
		struct Color4 : Color3
		{
			float a = 1.f;
			Color4(float r, float g, float b, float a) : Color3(r,g,b), a(a) {};
			Color4(float r, float g, float b) : Color3(r,g,b) {};
			Color4(Color3 c) : Color3(c) {}
		};



		struct Resolution
		{
			UINT width;
			UINT height;
		};
		
		struct Position
		{
			float x; float y;
		};
	}
}
