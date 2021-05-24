#pragma once
#include <Windows.h>

namespace Application
{
	namespace Interaction
	{
		class IEventHandler
		{
		protected:
			bool can_handle_event = true;
		protected:
			virtual void on_lbmouse_down() PURE;
			virtual void on_lbmouse_up() PURE;
			virtual void on_mouse_scroll(short direction) PURE;
			virtual void on_mouse_move(int mx,int my) PURE;
		};
	}
}
