#pragma once
#include "../GBHRC/includes/win.h"
#include "Managers/RectangleManager.h"
#include "Render/Render.h"

#define FIELD_SETTER(field_type,field_name) void set_##field_name(field_type field_name){this->##field_name = field_name;}

namespace Application
{
	class InteractiveForm;
	
	void implement(HWND hwnd);

	void register_form(InteractiveForm* form);
	void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);

	Render::Resolution get_window_resolution();

	POINT get_client_cursor_point();

	Render::Position point_to_center(Render::Position pos);
	POINT point_to_center(POINT p);
}
