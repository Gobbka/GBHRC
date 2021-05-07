#pragma once
#include "../GBHRC/includes/win.h"
#include "Managers/RectangleManager.h"
#include "Render/Render.h"

namespace Application
{
	class InteractiveForm;
	
	void implement(HWND hwnd);

	void register_form(InteractiveForm* form);
	void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);

	Render::Resolution get_window_resolution();

	POINT get_client_cursor_point();
	POINT point_to_center(POINT p);
}
