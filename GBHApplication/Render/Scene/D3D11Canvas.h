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
			struct Allocator
			{
				UINT start_size;
				UINT step_size;
				UINT allocated;
				Allocator(UINT start_size,UINT step_size)
				{
					this->start_size = start_size;
					this->step_size = step_size;
					this->allocated = 0;
				}
			};
		private:
			Render::Engine* engine;
			Allocator allocator;
			
			GVertex::VertexBuffer* alloc_vbuffer(UINT size) const;
			void set_vbuffer(GVertex::VertexBuffer* buffer);

			
		protected:
			GVertex::VertexBuffer* vertex_buffer;

		protected:
			UINT buffer_size() const;
			UINT get_allocated_size() const;
			
			Render::Engine* get_engine() const;

			virtual void update() const;

			void alloc_vertexes(UINT size);
			
		public:
			GVertex::Vertex* get_ptr() const;
			GVertex::VertexBuffer* get_vbuffer() const;


			D3D11Canvas(Render::Engine* pEngine,GVertex::VertexBuffer* buffer);
			D3D11Canvas(Render::Engine* pEngine);
			~D3D11Canvas();
		};
	}
}
