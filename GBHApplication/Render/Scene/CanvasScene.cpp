#include "CanvasScene.h"
#include "../../Render/Engine/Engine.h"
#include "../../Application.h"

#define DRAW_ASSERT if(this->hidden==true) return

void Application::Render::CanvasScene::render_components(Render::DrawEvent*draw_event)
{
	if (this->pre_render_callback != nullptr)
		pre_render_callback(draw_event);

	for (auto* element : this->pElements)
		CanvasScene::draw_element(element, draw_event);

	if (this->render_callback != nullptr)
		render_callback(draw_event);
}

void Application::Render::CanvasScene::draw_element(Canvas::CanvasElement* obj, Render::DrawEvent* event)
{
	if(obj->render == true)
		event->draw_element(obj);
}

void Application::Render::CanvasScene::initialize_components(Application::Render::Engine* pEngine)
{
	D3D11Canvas::alloc_vbuffer(this->count_size());

	UINT size = 0;

	CanvasScene::foreach([&size, this](Canvas::CanvasElement* obj)
		{
			obj->set_index(size);
			obj->initialize(this);
			size += obj->size();
		});
}

void Application::Render::CanvasScene::update(Render::Engine* pEngine)
{
	DRAW_ASSERT;

	D3D11Canvas::update();
}

void Application::Render::CanvasScene::render(Render::DrawEvent* draw_event)
{
	DRAW_ASSERT;

	draw_event->engine->set_vbuffer(this->get_vbuffer());

	this->render_components(draw_event);
}

void Application::Render::CanvasScene::foreach(std::function<void(Canvas::CanvasElement*)> const& callback)
{
	for (auto* element : this->pElements)
		callback(element);
}

UINT Application::Render::CanvasScene::count_size()
{
	UINT size = 0;
	for (auto* element : this->pElements)
		size += element->size();
	return size;
}

void Application::Render::CanvasScene::add_element(Canvas::CanvasElement* object)
{
	if(this->components_initialized == false)
	{
		this->pElements.push_back(object);
		return;
	}
	// TODO: make realloc memory
}

void Application::Render::CanvasScene::set_indexes()
{
	UINT index = 0;
	this->foreach([&index](Canvas::CanvasElement* obj)
		{
			obj->set_index(index);
			index += obj->size();
		});
}

Application::Canvas::CanvasElement* Application::Render::CanvasScene::element_at(UINT index)
{
	return this->pElements[index];
}

Application::Render::CanvasScene::CanvasScene(Render::Engine* pEngine)
	: D3D11Canvas(pEngine)
{
}

size_t Application::Render::CanvasScene::elements_length() const
{
	return this->pElements.size();
}
