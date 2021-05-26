#pragma once
#include "../d3d/Vertex.h"

namespace Application
{
	namespace Render
	{
		class Engine;

		class D3D11Canvas
		{
		protected:
			GVertex::VertexBuffer* vertex_buffer;

		protected:
			UINT size() const;

			void update(Render::Engine* pEngine) const;
			void alloc_vbuffer(Render::Engine* pEngine,UINT size);
		public:
			GVertex::Vertex* get_ptr() const;
			GVertex::VertexBuffer* get_vbuffer() const;


			D3D11Canvas(GVertex::VertexBuffer* buffer);
			D3D11Canvas();
			~D3D11Canvas();
		};
	}
}
