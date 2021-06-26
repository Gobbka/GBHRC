#pragma once
#include <d3d11.h>

#include "../Render.h"
#include "../d3d/Buffers/ConstantBuffer.h"

namespace Application {
	namespace Canvas {
		class CanvasElement;
	}
}

namespace GVertex {
	struct Vertex;
}

namespace Application
{
	namespace Render
	{
		class IRenderObject;
		class Engine;
		class CanvasScene;

		struct D3D11DrawEvent
		{
			Engine* engine;
			CanvasScene* scene;
			ID3D11RasterizerState* old_state;
			
			unsigned int scenes_completed;
		private:
			UINT element_index;
			BYTE mask_layer_depth;
		public:
			void set_alpha(float alpha);
			
			void draw_element(Canvas::CanvasElement*object);
			void draw_vertex(UINT count,UINT offset=0) const;

			void mask_draw_begin() const;
			void mask_discard_begin(bool increase_layer = true);
			void mask_discard_end(bool decrease_layer = true);
			void mask_set_depth(BYTE new_index);
			BYTE mask_get_depth();
			void mask_clear();
			void mask_reset();

			ID3D11DeviceContext* get_context() const;
			void reset_render_state();

			D3D11DrawEvent(Engine* engine, CanvasScene* scene, ID3D11RasterizerState* old_state);
		};

	}
}
