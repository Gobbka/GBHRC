#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include <windowsx.h>

void Application::InteractiveForm::window_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE)
	{
		POINT center{ (LONG)(this->resolution.width / 2),(LONG)(this->resolution.height / 2) };

		const POINT cursor{ GET_X_LPARAM(lParam) - center.x , center.y - GET_Y_LPARAM(lParam) };

		if (this->dragged)
		{
			this->dragged->element->set_pos(cursor.x - 5, cursor.y + 5);
			return;
		}
		
		const auto length = this->total_size() - 1;
		bool e_handled = false;
		
		for (int i = length; i >= 0; i--)
		{
			auto* element = (UI::InteractiveElement*)this->element_at(i);
			if (
				e_handled == false &&
				element->point_belongs(cursor)
			)
			{
				if (element->hovered == false)
				{
					element->hovered = true;
					element->onMouseEnter(element);
				}
				element->onMouseMove(element,cursor.x,cursor.y);
				e_handled = true;
			}
			else if (element->hovered == true)
			{
				element->onMouseLeave(element);
				element->hovered = false;
			}
		}

		return;
	}

	if (msg == WM_LBUTTONUP)
	{
		this->foreach([](Render::IRenderObject* obj)
			{
				auto* element = (UI::InteractiveElement*)obj;
				if (element->hovered == true)
					element->onMouseUp(element);
			});

		this->free_drag_move();

		return;
	}

	if (msg == WM_LBUTTONDOWN)
	{
		this->foreach([](Render::IRenderObject*obj)
			{
				auto* element = (UI::InteractiveElement*)obj;
				if (element->hovered == true)
					element->onMouseDown(element);
			});
		return;
	}
}

void Application::InteractiveForm::drag_move(UI::InteractiveElement* element)
{
	this->dragged = new DragStruct{ 0,0 ,element};
}

void Application::InteractiveForm::free_drag_move()
{
	if (this->dragged == nullptr) return;

	delete this->dragged;
	this->dragged = nullptr;
}

void Application::InteractiveForm::update_markup(Render::Engine* pEngine)
{
	this->alloc_vbuffer(pEngine);
	UINT size = 0;
	Scene::foreach([this, &size](Render::IRenderObject* obj)
		{
			auto* iUIObject = (UI::InteractiveElement*)obj;
			iUIObject->set_index(size);
			iUIObject->init(this);

			size += obj->size();
		});
}

void Application::InteractiveForm::add_elements(UINT count, UI::InteractiveElement* element, ...)
{
	va_list v1;
	va_start(v1, count);

	for (UINT i = 0; i < count; i++)
	{
		this->add_render_object(va_arg(v1, UI::InteractiveElement*));
	}
}

