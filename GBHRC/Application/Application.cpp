#include "Application.h"
#include "Form/Form.h"
#include <vector>

std::vector<Application::Form*> _registered_forms;

void Application::register_form(Form* form)
{
	_registered_forms.push_back(form);
}

void Application::wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	for (auto* form : _registered_forms)
		form->window_proc(msg, wParam, lParam);
}
