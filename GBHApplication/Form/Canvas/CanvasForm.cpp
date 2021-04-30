#include "CanvasForm.h"

#include "elements/IElement/IElement.h"

void Application::Canvas::CanvasForm::update_markup(Application::Render::Engine* pEngine)
{
	this->alloc_vbuffer(pEngine);
	UINT size = 0;
	
	Scene::foreach([&size,this](Render::IRenderObject* obj)
		{
			((Canvas::IElement*)obj)->set_index(size);
			((Canvas::IElement*)obj)->init(this);
			size += obj->size();
		});
}

void Application::Canvas::CanvasForm::add_elements(UINT count,Canvas::IElement* element...)
{
	va_list v1;
	va_start(v1, count);

	for (UINT i = 0; i < count; i++)
	{
		this->add_render_object(va_arg(v1, Canvas::IElement*));
	}
}
