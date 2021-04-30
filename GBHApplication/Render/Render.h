#pragma once
#include "../../GBHRC/includes/d3d.h"
#include "../../GBHRC/includes/logger.h"
#include "../../GBHRC/includes/win.h"

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

		class Engine;
		class Scene;
	}
}


#include "d3d/Vertex.h"
#include "d3d/ConstantBuffer.h"
#include "d3d/szShadez.h"
#include "Engine/Engine.h"
#include "Scene/Scene.h"
