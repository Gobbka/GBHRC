#include "WinIntEventHandler.h"

void Application::Interaction::WinIntEventHandler::window_proc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!this->can_handle_event)
		return;

	
}
