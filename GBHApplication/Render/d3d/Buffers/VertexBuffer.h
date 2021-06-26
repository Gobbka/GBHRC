#pragma once
#include <d3d11.h>
#include "../Bindable.h"

namespace GVertex {
	struct Vertex;
}

namespace Render
{
	class VertexBuffer : Application::Render::Bindable
	{
	private:
		ID3D11Buffer* _buffer = nullptr;
	public:
		GVertex::Vertex* data = nullptr;
		UINT size = 0;

		void copy_to(VertexBuffer* buffer) const;
		void copy_to(void* buffer, UINT size) const;
	public:
		VertexBuffer(Application::Render::Engine* engine,GVertex::Vertex*data,UINT size,bool dynamic=true);
		~VertexBuffer();
		
		void bind() override;
		void update(UINT update_size=-1);
	};
}
