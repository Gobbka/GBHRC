#include "Form.h"

void Application::Form::window_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE)
	{
		POINT center{ (LONG)(this->resolution.width / 2),(LONG)(this->resolution.height / 2) };

		const POINT cursor{ GET_X_LPARAM(lParam) - center.x , center.y - GET_Y_LPARAM(lParam) };

		const auto length = this->pElements.size() - 1;
		bool e_handled = false;
		
		for (int i = length; i >= 0; i--)
		{
			auto* element = this->pElements[i];
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
		for (auto* element : this->pElements)
			if (element->hovered == true)
				element->onMouseUp(element);
		return;
	}

	if (msg == WM_LBUTTONDOWN)
	{
		for (auto* element : this->pElements)
			if (element->hovered == true)
				element->onMouseDown(element);
		return;
	}
}
