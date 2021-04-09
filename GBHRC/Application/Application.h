#pragma once

#include "../includes/d3d.h"
#include "../includes/logger.h"
#include "../includes/win.h"

namespace Application
{
	namespace Render
	{
		struct Resolution
		{
			UINT width;
			UINT height;
		};

		struct Position
		{
			float x; float y; float width; float height;
		};

		class Engine;
		class Scene;
	}

	namespace UI
	{
		class IElement;
	}
}


#include "Render/d3d/Vertex.h"
#include "Render/d3d/ConstantBuffer.h"
#include "Render/d3d/szShadez.h"
#include "Render/Engine/Engine.h"
#include "Render/Scene/Scene.h"

#include "UI/IElement/IElement.h"
