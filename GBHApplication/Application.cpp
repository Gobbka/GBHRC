#include "Application.h"
#include "Form/Interactive/InteractiveForm.h"
#include "Form/Interactive/Events/WinIntEventHandler.h"

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

Application::Render::Resolution Application::Context::get_window_resolution()
{
	return AppContext->AppResolution;
}

Application::Render::Position Application::Context::get_client_cursor_point()
{
	return AppContext->cursor_point;
}

Application::Animator* Application::Context::get_animator()
{
	return &AppContext->animator;
}

Application::Render::Position Application::Context::point_to_center(Render::Position p)
{
	auto res = Application::Context::get_window_resolution();

	return { p.x - (res.width / 2),(res.height / 2) - p.y };
}

Application::Render::Position Application::Context::point_to_window(Render::Position p)
{
	auto res = Application::Context::get_window_resolution();
	return { p.x + res.width / 2, res.height / 2 - p.y };
}

POINT Application::Context::point_to_center(POINT p)
{
	auto rect = Application::Context::get_window_resolution();

	return { (LONG)p.x - (LONG)(rect.width) / 2,(LONG)(rect.height) / 2 - (LONG)p.y };
}

void Application::Context::on_lbmouse_down()
{
	for (auto* form : AppContext->_registered_forms)
		if (form->on_lbmouse_down() == Interaction::EventStatus::handled)
			return;
}

void Application::Context::on_lbmouse_up()
{
	for (auto* form : AppContext->_registered_forms)
		if (form->on_lbmouse_up() == Interaction::EventStatus::handled)
			return;
}

void Application::Context::on_mouse_scroll(short direction)
{
	for (auto* form : AppContext->_registered_forms)
		if (form->on_mouse_scroll(direction) == Interaction::EventStatus::handled)
			return;
}

void Application::Context::on_mouse_move(int mx, int my)
{
	this->cursor_point = (Render::Position{ (float)mx,(float)my });

	for (auto iteration = AppContext->_registered_forms.size(); iteration >0; iteration--)
	{
		if (AppContext->_registered_forms[iteration-1]->on_mouse_move(cursor_point.x,cursor_point.y) == Interaction::EventStatus::handled)
		{
			return;
		}
	}
	
	//for (auto* form : AppContext->_registered_forms)
	//{
	//	if (form->on_mouse_move(mx, my) == Interaction::EventStatus::handled)
	//	{
	//		DEBUG_LOG("NIGGER");
	//		return;
	//	}
	//}
		
}

