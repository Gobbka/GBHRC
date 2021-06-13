#pragma once
#include "../d3d/Vertex.h"

namespace Application
{
	namespace Render
	{
		class Engine;

		class D3D11Canvas
		{
		private:
			Render::Engine* engine;
		protected:
			GVertex::VertexBuffer* vertex_buffer;

		protected:
			UINT size() const;

			void update() const;
			void alloc_vbuffer(UINT size);
		public:
			GVertex::Vertex* get_ptr() const;
			GVertex::VertexBuffer* get_vbuffer() const;


			D3D11Canvas(Render::Engine* pEngine,GVertex::VertexBuffer* buffer);
			D3D11Canvas(Render::Engine* pEngine);
			~D3D11Canvas();
		};
	}
}
