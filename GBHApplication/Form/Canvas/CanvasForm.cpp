#include "CanvasForm.h"

#include "elements/IElement/CanvasElement.h"
#include "../../Render/Engine/Engine.h"

void Application::Canvas::CanvasForm::draw_element(Render::IRenderObject* obj, Render::DrawEvent* event)
{
	if (((Canvas::CanvasElement*)obj)->render == true)
		event->draw_element(obj);
}

void Application::Canvas::CanvasForm::update_markup(Application::Render::Engine* pEngine)
{

	this->alloc_vbuffer(pEngine);
	UINT size = 0;
	
	Scene::foreach([&size,this](Render::IRenderObject* obj)
		{
			((Canvas::CanvasElement*)obj)->set_index(size);
			((Canvas::CanvasElement*)obj)->init(this);
			size += obj->size();
		});
}

Application::Canvas::CanvasForm* Application::Canvas::CanvasForm::add_element(CanvasElement* element)
{
	this->add_render_object(element);
	return this;
}
