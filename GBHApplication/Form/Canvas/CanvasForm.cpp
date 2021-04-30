#include "CanvasForm.h"

#include "elements/IElement/CanvasElement.h"

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

void Application::Canvas::CanvasForm::add_elements(UINT count,Canvas::CanvasElement* element...)
{
	va_list v1;
	va_start(v1, count);

	for (UINT i = 0; i < count; i++)
	{
		this->add_render_object(va_arg(v1, Canvas::CanvasElement*));
	}
}
