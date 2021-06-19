#pragma once
#include "../../GBHRC/includes/d3d.h"
#include "../../GBHRC/includes/logger.h"
#include "../../GBHRC/includes/win.h"
#include "Events/EngineEvents.h"

namespace Application
{
	namespace Render
	{
		struct Color
		{
			float r; float g; float b; float a;
			Color(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {};
			Color(float r, float g, float b,float a) : r(r), g(g), b(b), a(a) {};
			Color(DirectX::XMFLOAT3 f3) : r(f3.x), g(f3.y), b(f3.z) {};
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
