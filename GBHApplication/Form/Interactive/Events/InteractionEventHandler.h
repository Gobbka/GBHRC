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
			virtual void on_mouse_down() PURE;
			virtual void on_mouse_up() PURE;
			virtual void on_mouse_scroll() PURE;
			virtual void on_mouse_move() PURE;
		};
	}
}
