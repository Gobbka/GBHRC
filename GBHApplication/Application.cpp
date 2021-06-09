#include "Application.h"
#include "Form/Interactive/InteractiveForm.h"

Application::Context* AppContext;

Application::Context::Context(HWND window)
	:animator()
{
	RECT wndRect;
	GetClientRect(window, &wndRect);

	this->AppResolution = { (UINT)wndRect.right,(UINT)wndRect.bottom };
	this->main_window = window;
	this->animator.start();
}

void Application::Context::implement(HWND hwnd)
{
	AppContext = new Application::Context(hwnd);
}

void Application::Context::register_form(InteractiveForm* form)
{
	//form->set_resolution(AppResolution);
	AppContext->_registered_forms.push_back(form);
}

void Application::Context::wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_MOUSEMOVE)
	{
		AppContext->cursor_point = lParam;
	}
	
	for (auto* form : AppContext->_registered_forms)
		form->window_proc(msg, wParam, lParam);
}

Application::Render::Resolution Application::Context::get_window_resolution()
{
	return AppContext->AppResolution;
}

POINT Application::Context::get_client_cursor_point()
{
	return { GET_X_LPARAM(AppContext->cursor_point),GET_Y_LPARAM(AppContext->cursor_point) };
	//RECT rect;
	//POINT point;

	//GetWindowRect(AppContext->main_window, &rect);
	//GetCursorPos(&point);
	//DEBUG_LOG("MOUSE: " << point.x << " " << point.y);
	//DEBUG_LOG("RECT: " << rect.left << " " << rect.top);
	//return { point.x - rect.left,point.y - rect.top };
}

Application::Animator* Application::Context::get_animator()
{
	return &AppContext->animator;
}

Application::Render::Position Application::Context::point_to_center(Render::Position p)
{
	auto res = Application::Context::get_window_resolution();

	return { p.x + res.width / 2,res.height / 2 - p.y };
}

POINT Application::Context::point_to_center(POINT p)
{
	auto rect = Application::Context::get_window_resolution();

	return { (LONG)p.x - (LONG)(rect.width) / 2,(LONG)(rect.height) / 2 - (LONG)p.y };
}

