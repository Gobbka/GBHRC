#include "InteractiveForm.h"
#include "elements/IElement/IElement.h"
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
		
		const auto length = this->pElements.size() - 1;
		bool e_handled = false;
		
		for (int i = length; i >= 0; i--)
		{
			auto* element = (UI::IElement*)this->pElements[i];
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
		this->foreach([](UI::IElement* element)
			{
				if (element->hovered == true)
					element->onMouseUp(element);
			});

		this->free_drag_move();

		return;
	}

	if (msg == WM_LBUTTONDOWN)
	{
		this->foreach([](UI::IElement*element)
			{
				if (element->hovered == true)
					element->onMouseDown(element);
			});
		return;
	}
}

void Application::InteractiveForm::drag_move(UI::IElement* element)
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
	for (auto* element : this->pElements)
	{
		auto* iUIObject = (UI::IElement*)element;
		iUIObject->set_index(size);
		iUIObject->init(this);

		size += element->size();
	}
}

void Application::InteractiveForm::foreach(void(* callback)(UI::IElement*))
{
	for(auto*iRenderElement:this->pElements)
	{
		auto* ui_element = (UI::IElement*)iRenderElement;
		callback(ui_element);
	}
}
