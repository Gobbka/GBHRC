#include "CanvasForm.h"

#include "elements/IElement/CanvasElement.h"
#include "../../Render/Engine/Engine.h"

void Application::Canvas::CanvasForm::draw_element(Render::IRenderObject* obj, Render::DrawEvent* event)
{
	event->engine->get_mask()->set_draw_mask();
	event->engine->pDevContext->PSSetShader(nullptr, nullptr, 0);
	
	if (((Canvas::CanvasElement*)obj)->render == true)
		obj->draw(event);
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

void Application::Canvas::CanvasForm::add_element(CanvasElement* element)
{
	this->add_render_object(element);
}
