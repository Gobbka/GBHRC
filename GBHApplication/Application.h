#pragma once
#include <vector>

#include "../GBHRC/includes/win.h"
#include "Managers/Animation/Animator.h"
#include "Render/Render.h"


#define FIELD_SETTER(field_type,field_name) void set_##field_name(field_type field_name){this->##field_name = field_name;}

namespace Application
{
	namespace Interaction {
		class WinIntEventHandler;
	}
	#ifdef WIN32
		typedef Interaction::WinIntEventHandler OS_EVENT_HANDLER;
	#else
		static_assert(1,"UNSUPORTED OS");
	#endif

	class InteractiveForm;
	
	class Context
	{
		std::vector<Application::InteractiveForm*> _registered_forms;
		Application::Render::Resolution AppResolution;
		HWND main_window;
		Animator animator;
		unsigned long long cursor_point;

		Context(HWND window);
	public:
		static void implement(HWND hwnd);

		static void register_form(InteractiveForm* form);
		static void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);

		static Render::Resolution get_window_resolution();

		static POINT get_client_cursor_point();

		static Animator* get_animator();

		static Render::Position point_to_center(Render::Position pos);
		static POINT point_to_center(POINT p);
	};
}
