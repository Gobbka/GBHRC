#include "Application.h"
#include "Form/Interactive/InteractiveForm.h"
#include "Form/Interactive/Events/WinIntEventHandler.h"
#include "Render/Engine/Engine.h"

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

void Application::Context::set_engine(Render::Engine* engine)
{
	AppContext->engine = engine;
}

Application::InteractiveForm* Application::Context::create_form()
{
	auto* form = new InteractiveForm(AppContext->engine);
	AppContext->register_form(form);
	return form;
}

Application::Render::CanvasScene* Application::Context::create_canvas()
{
	auto* canvas = new Render::CanvasScene(AppContext->engine);
	AppContext->engine->append_scene(canvas);
	return canvas;
}

void Application::Context::register_form(InteractiveForm* form)
{
	AppContext->_registered_forms.push_back(form);
	AppContext->engine->append_scene(form);
}

void Application::Context::remove_form(InteractiveForm* form)
{
	auto* forms = &AppContext->_registered_forms;
	for (int i = 0; i < forms->size(); i++)
	{
		if (form == (*forms)[i])
		{
			AppContext->_registered_forms.erase(forms->begin() + i);
			return;
		}
	}
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

	for (auto iteration = AppContext->_registered_forms.size(); iteration --> 0;)
	{
		if (AppContext->_registered_forms[iteration]->on_mouse_move(cursor_point.x,cursor_point.y) == Interaction::EventStatus::handled)
		{
			return;
		}
	}
		
}

