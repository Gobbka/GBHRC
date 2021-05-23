#include "Scene.h"
#include "../../Render/Engine/Engine.h"
#include "../../Application.h"

#define DRAW_ASSERT if(this->hidden==true) return

void Application::Render::Scene::alloc_vbuffer(Render::Engine* pEngine)
{
	delete this->pVBuffer;
	const UINT size = this->total_size();

	this->pVBuffer = pEngine->make_vertex_buffer(size);
}

void Application::Render::Scene::update(Render::Engine* pEngine)
{
	DRAW_ASSERT;

	if (this->pVBuffer->size <= 0)
		return;

	auto* pContext = pEngine->pDevContext;
	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(this->pVBuffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	memcpy(subdata.pData, this->pVBuffer->data, this->pVBuffer->size * sizeof(GVertex::Vertex));
	pContext->Unmap(this->pVBuffer->buffer, 0);
}

void Application::Render::Scene::render(Render::DrawEvent* draw_event)
{
	DRAW_ASSERT;

	draw_event->engine->set_vbuffer(this->get_vbuffer());

	if (this->pre_render_callback != nullptr)
		pre_render_callback(draw_event);
	
	for (auto* element : this->pElements)
		this->draw_element(element, draw_event);
		//element->__draw(draw_event);

	if (this->render_callback != nullptr)
		render_callback(draw_event);
}

void Application::Render::Scene::foreach(std::function<void(IRenderObject*)> const& callback)
{
	for (auto* element : this->pElements)
		callback(element);
}

UINT Application::Render::Scene::total_size()
{
	UINT size = 0;
	for (auto* element : this->pElements)
		size += element->size();
	
	return size;
}

void Application::Render::Scene::add_render_object(IRenderObject* object)
{
	this->pElements.push_back(object);
}

Application::Render::IRenderObject* Application::Render::Scene::element_at(UINT index)
{
	return this->pElements[index];
}

Application::Render::Resolution Application::Render::Scene::get_screen_resolution() const
{
	return this->screen_resolution;
}

void Application::Render::Scene::set_resolution(Resolution resolution)
{
	this->screen_resolution = resolution;
}

UINT Application::Render::Scene::elements_length() const
{
	return this->pElements.size();
}


GVertex::Vertex* Application::Render::Scene::get_ptr() const
{
	return this->pVBuffer->data;
}

GVertex::VertexBuffer* Application::Render::Scene::get_vbuffer()
{
	return  this->pVBuffer;
}

Application::Render::Scene::~Scene()
{
	delete this->pVBuffer;
}
