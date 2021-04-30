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

