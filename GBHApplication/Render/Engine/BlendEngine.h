#pragma once
#include <d3d11.h>

namespace Render {
	class ConstantBuffer;
}

struct ConstantBuffer;
namespace Application
{
	namespace Render
	{
		class Engine;

		class BlendEngine
		{
			ID3D11BlendState* blend_state;
			Engine* engine;
		public:
			BlendEngine(Engine*engine);

			void set_blend_state();

			void set_alpha(::Render::ConstantBuffer* buffer,float alpha);
		};
	}
}
