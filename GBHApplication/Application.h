#pragma once
#include <vector>

#include "../GBHRC/includes/win.h"
#include "Managers/Animation/Animator.h"
#include "Render/Render.h"


#define FIELD_SETTER(field_type,field_name) void set_##field_name(field_type field_name){this->##field_name = field_name;}

#ifdef WIN32
#include "Form/Interactive/Events/WinIntEventHandler.h"
typedef Application::Interaction::WinIntEventHandler OS_EVENT_HANDLER;
#else
static_assert(1, "UNSUPORTED OS");
#endif

namespace Application
{
	class InteractiveForm;
	
	class Context final : public OS_EVENT_HANDLER
	{
		std::vector<Application::InteractiveForm*> _registered_forms;
		OS_EVENT_HANDLER* os_event_handler;
		Application::Render::Resolution AppResolution;
		HWND main_window;
		Animator animator;
		Render::Position cursor_point;
		Render::Engine* engine;

		Context(HWND window);

		
	public:
		static void implement(HWND hwnd);
		static void set_engine(Render::Engine* engine);
		
		static InteractiveForm* create_form();
		static void register_form(InteractiveForm* form);
		static void remove_form(InteractiveForm* form);

		static Render::Resolution get_window_resolution();

		static Render::Position get_client_cursor_point();

		static Animator* get_animator();

		static Render::Position point_to_center(Render::Position pos);
		static Render::Position point_to_window(Render::Position pos);
		static POINT point_to_center(POINT p);
	protected:
		void on_lbmouse_down() override;
		void on_lbmouse_up() override;
		void on_mouse_scroll(short direction) override;
		void on_mouse_move(int mx, int my) override;
	};
}
