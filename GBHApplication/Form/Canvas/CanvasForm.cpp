#include "CanvasForm.h"

#include "elements/IElement/CanvasElement.h"
#include "../../Render/Engine/Engine.h"

void Application::Canvas::CanvasForm::draw_element(Render::IRenderObject* obj, Render::DrawEvent* event)
{
	if (((Canvas::CanvasElement*)obj)->render == true)
	{
		//event->engine->get_mask()->set_draw_mask();
		//event->draw_element(obj);
		//event->engine->get_mask()->unset_mask();
		//obj->draw(event);
		//event->engine->set_vbuffer(this->get_vbuffer());
		//event->engine->get_mask()->set_discard_mask();
		//event->engine->pDevContext->Draw(4, 0);
		event->draw_element(obj);
	}

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
