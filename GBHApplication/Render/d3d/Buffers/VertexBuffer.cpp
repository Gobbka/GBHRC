#include "VertexBuffer.h"
#include "../../Engine/Engine.h"

void Render::VertexBuffer::copy_to(VertexBuffer* buffer) const
{
	const auto copy_size = min(this->size, buffer->size);

	memcpy(buffer->data, this->data, copy_size * sizeof(GVertex::Vertex));
}

void Render::VertexBuffer::copy_to(void* buffer, UINT size) const
{
	memcpy(buffer, this->data, size * sizeof(GVertex::Vertex));
}

Render::VertexBuffer::VertexBuffer(Application::Render::Engine* engine, GVertex::Vertex* data, UINT size, bool dynamic)
	: Bindable(engine)
{
	this->data = data;
	this->size = size;
	
	D3D11_BUFFER_DESC vbuffer{
		sizeof(GVertex::Vertex) * size,
		dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		dynamic ? D3D11_CPU_ACCESS_WRITE : 0,
		0,
		sizeof(GVertex::Vertex)
	};
	D3D11_SUBRESOURCE_DATA sd{ data,0,0 };
	
	if(FAILED(_engine->pDevice->CreateBuffer(&vbuffer, &sd, &_buffer)))
	{
		DEBUG_LOG("CANNOT CREATE VBUFFER");
	}
}

Render::VertexBuffer::~VertexBuffer()
{
	if (_buffer)
		_buffer->Release();
	delete[] data;
}

void Render::VertexBuffer::bind()
{
	UINT stride = sizeof(GVertex::Vertex);
	UINT offset = 0;
	_engine->pDevContext->IASetVertexBuffers(0, 1, &_buffer, &stride, &offset);
}

void Render::VertexBuffer::update(UINT update_size)
{
	update_size = min(update_size, this->size);

	auto* pContext = _engine->pDevContext;
	D3D11_MAPPED_SUBRESOURCE subdata;
	
	pContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	
	this->copy_to(subdata.pData, update_size);
	
	pContext->Unmap(_buffer, 0);
}
