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
			float r; float g; float b;
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
