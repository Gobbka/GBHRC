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
			ID3D11RasterizerState* old_state;

			unsigned int scenes_completed;
			bool has_texts;

			ID3D11DeviceContext* get_context() const;
			void reset_render_state();
		};

	}
}
