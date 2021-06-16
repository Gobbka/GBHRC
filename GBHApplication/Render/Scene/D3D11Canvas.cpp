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

UINT Application::Render::D3D11Canvas::buffer_size() const
{
	return this->vertex_buffer->size;
}

UINT Application::Render::D3D11Canvas::get_allocated_size() const
{
	return this->allocator.allocated;
}

Application::Render::Engine* Application::Render::D3D11Canvas::get_engine() const
{
	return this->engine;
}

void Application::Render::D3D11Canvas::update() const
{
	if (this->vertex_buffer->size <= 0)
		return;

	auto* pContext = engine->pDevContext;
	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(this->vertex_buffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	this->vertex_buffer->copy_to(subdata.pData, this->allocator.allocated);
	pContext->Unmap(this->vertex_buffer->buffer, 0);
}

void Application::Render::D3D11Canvas::alloc_vertexes(UINT size)
{
	if(this->allocator.allocated + size > this->buffer_size())
	{
		const int needed = (this->allocator.allocated + size) / allocator.step_size + 1;

		auto* new_buffer = this->alloc_vbuffer(needed * this->allocator.step_size);
		this->vertex_buffer->copy_to(new_buffer);
		this->set_vbuffer(new_buffer);
	}

	this->allocator.allocated += size;
}

GVertex::VertexBuffer* Application::Render::D3D11Canvas::alloc_vbuffer(UINT size) const
{
	return engine->make_vertex_buffer(size);
}

void Application::Render::D3D11Canvas::set_vbuffer(GVertex::VertexBuffer* buffer)
{
	delete this->vertex_buffer;
	this->vertex_buffer = buffer;
}

Application::Render::D3D11Canvas::D3D11Canvas(Render::Engine* pEngine,GVertex::VertexBuffer* buffer)
	:allocator(100,100)
{
	this->vertex_buffer = buffer;
	this->engine = pEngine;

	this->allocator.allocated = buffer->size;
}

Application::Render::D3D11Canvas::D3D11Canvas(Render::Engine* pEngine)
	:allocator(100, 100)
{
	this->vertex_buffer = nullptr;
	this->engine = pEngine;
	
	this->set_vbuffer(this->alloc_vbuffer(this->allocator.start_size));
}

Application::Render::D3D11Canvas::~D3D11Canvas()
{
	delete this->vertex_buffer;
}
