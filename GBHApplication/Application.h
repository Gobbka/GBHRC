#pragma once
#include "../GBHRC/includes/win.h"
#include "Managers/RectangleManager.h"

namespace Application
{
	class InteractiveForm;
	
	void implement(HWND hwnd);

	void register_form(InteractiveForm* form);
	void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);

}
