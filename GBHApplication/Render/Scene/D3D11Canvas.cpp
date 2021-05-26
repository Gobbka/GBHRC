#include "D3D11Canvas.h"
#include "../Engine/Engine.h"

GVertex::Vertex* Application::Render::D3D11Canvas::get_ptr() const
{
	return this->vertex_buffer->data;
}

GVertex::VertexBuffer* Application::Render::D3D11Canvas::get_vbuffer() const
{
	return  this->vertex_buffer;
}

UINT Application::Render::D3D11Canvas::size() const
{
	return this->vertex_buffer->size;
}

void Application::Render::D3D11Canvas::update(Render::Engine* pEngine) const
{
	if (this->vertex_buffer->size <= 0)
		return;

	auto* pContext = pEngine->pDevContext;
	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(this->vertex_buffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	memcpy(subdata.pData, this->vertex_buffer->data, this->vertex_buffer->size * sizeof(GVertex::Vertex));
	pContext->Unmap(this->vertex_buffer->buffer, 0);
}

void Application::Render::D3D11Canvas::alloc_vbuffer(Render::Engine* pEngine,UINT size)
{
	delete this->vertex_buffer;
	this->vertex_buffer = pEngine->make_vertex_buffer(size);
}

Application::Render::D3D11Canvas::D3D11Canvas(GVertex::VertexBuffer* buffer)
{
	this->vertex_buffer = buffer;
}

Application::Render::D3D11Canvas::D3D11Canvas()
{
	this->vertex_buffer = nullptr;
}

Application::Render::D3D11Canvas::~D3D11Canvas()
{
	delete this->vertex_buffer;
}
