#pragma once
#include <d3d11.h>

#include "../Render.h"

namespace GVertex {
	struct Vertex;
}

namespace Application
{
	namespace Render
	{
		class IRenderObject;
		class Engine;
		class Scene;

		struct DrawEvent
		{
			Engine* engine;
			Scene* scene;
			ID3D11RasterizerState* old_state;

			
			unsigned int scenes_completed;
		private:
			UINT element_ptr;
		public:
			
			void draw_element(Render::IRenderObject*object);
			void draw(UINT count,UINT offset=0);

			ID3D11DeviceContext* get_context() const;
			void reset_render_state();

			DrawEvent(Engine* engine, Scene* scene, ID3D11RasterizerState* old_state);
		};

	}
}
