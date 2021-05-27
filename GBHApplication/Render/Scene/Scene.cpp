#include "Scene.h"
#include "../../Render/Engine/Engine.h"
#include "../../Application.h"

#define DRAW_ASSERT if(this->hidden==true) return

void Application::Render::Scene::alloc_vbuffer(Render::Engine* pEngine)
{
	D3D11Canvas::alloc_vbuffer(pEngine, this->total_size());
}

void Application::Render::Scene::update(Render::Engine* pEngine)
{
	DRAW_ASSERT;

	D3D11Canvas::update(pEngine);
}

void Application::Render::Scene::render(Render::DrawEvent* draw_event)
{
	DRAW_ASSERT;

	draw_event->engine->set_vbuffer(this->get_vbuffer());

	if (this->pre_render_callback != nullptr)
		pre_render_callback(draw_event);
	
	for (auto* element : this->pElements)
		this->draw_element(element, draw_event);

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

void Application::Render::Scene::set_indexes()
{
	UINT index = 0;
	this->foreach([&index](IRenderObject* obj)
		{
			obj->set_index(index);
			index += obj->size();
		});
}

Application::Render::IRenderObject* Application::Render::Scene::element_at(UINT index)
{
	return this->pElements[index];
}

size_t Application::Render::Scene::elements_length() const
{
	return this->pElements.size();
}
