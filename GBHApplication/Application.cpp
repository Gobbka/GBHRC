#include "Application.h"

#include "Form/Interactive/InteractiveForm.h"
#include <vector>

std::vector<Application::InteractiveForm*> _registered_forms;
Application::Render::Resolution AppResolution;
HWND main_window;

void Application::implement(HWND hwnd)
{
	RECT wndRect;
	GetClientRect(hwnd, &wndRect);

	AppResolution = { (UINT)wndRect.right,(UINT)wndRect.bottom };
	
	main_window = hwnd;
}

void Application::register_form(InteractiveForm* form)
{
	form->set_resolution(AppResolution);
	_registered_forms.push_back(form);
}

void Application::wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	for (auto* form : _registered_forms)
		form->window_proc(msg, wParam, lParam);
}

Application::Render::Resolution Application::get_window_resolution()
{
	return AppResolution;
}

POINT Application::get_client_cursor_point()
{
	RECT rect;
	POINT point;

	GetWindowRect(main_window,&rect);
	GetCursorPos(&point);
	DEBUG_LOG("MOUSE: "<<point.x << " " << point.y);
	DEBUG_LOG("RECT: "<<rect.left << " " << rect.top);
	return { point.x - rect.left,point.y - rect.top };
}

POINT Application::point_to_center(POINT p)
{
	RECT rect;
	GetClientRect(main_window, &rect);

	return { p.x - (rect.right)/2,(rect.bottom)/2 - p.y  };
}

