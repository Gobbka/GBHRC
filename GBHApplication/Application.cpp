#include "Application.h"

#include "Form/Interactive/InteractiveForm.h"
#include <vector>

std::vector<Application::InteractiveForm*> _registered_forms;

HWND main_window;

void Application::implement(HWND hwnd)
{
	main_window = hwnd;
}

void Application::register_form(InteractiveForm* form)
{
	_registered_forms.push_back(form);
}

void Application::wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	for (auto* form : _registered_forms)
		form->window_proc(msg, wParam, lParam);
}

//POINT Application::nigger()
//{
//	POINT cursor_point;
//	RECT client_rect;
//
//	GetCursorPos(&cursor_point);
//	GetClientRect(main_window, &client_rect);
//
//	POINT center{ (client_rect.right - client_rect.left) / 2,(client_rect.bottom - client_rect.top) / 2 };
//	return { cursor_point.x - center.x,center.y - cursor_point.y };
//}

