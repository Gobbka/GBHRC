#pragma once
#include <d3d11.h>

#include "../Render.h"

namespace Application
{
	namespace Render
	{
		class Engine;
		class Scene;

		struct DrawEvent
		{
			Engine* engine;
			Scene* scene;

			unsigned int scenes_completed;
			bool has_texts;

			ID3D11DeviceContext* get_context() const;
		};

	}
}
