#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include "../../Application.h"
#include <windowsx.h>

void Application::InteractiveForm::window_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (this->hidden == true)
		return;
	
	if (msg == WM_MOUSEMOVE)
	{
		POINT center{ (LONG)(this->screen_resolution.width / 2),(LONG)(this->screen_resolution.height / 2) };

		const POINT cursor{ GET_X_LPARAM(lParam) - center.x , center.y - GET_Y_LPARAM(lParam) };

		if (this->dragged)
		{
			this->dragged->element->set_pos(cursor.x - this->dragged->dragged_offset.x, cursor.y + this->dragged->dragged_offset.y);
			return;
		}
		
		const auto length = this->elements_length() - 1;
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
	auto pos = element->get_position();
	auto cursor = ( Application::get_client_cursor_point()); // Application::point_to_center
	DEBUG_LOG(std::dec<< cursor.x << " " << cursor.x << " " << pos.x << " "<<pos.y);
	//this->dragged = new DragStruct{ cursor.x - (LONG)pos.x ,cursor.y - (LONG)pos.y ,element};
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
			iUIObject->set_form(this);
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

Application::InteractiveForm* Application::InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->add_render_object(element);
	return this;
}

