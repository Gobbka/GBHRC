#pragma once
#include "../../Application.h"

namespace Application
{
	class InteractiveForm : public Render::Scene
	{		
	public:
		struct DragStruct
		{
			POINT dragged_offset;
			UI::IElement* element;
		};
	private:
		DragStruct* dragged = nullptr;
	public:
		void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
		void drag_move(UI::IElement* element);
		void free_drag_move();

		void update_markup(Render::Engine* pEngine);

		void foreach(void(__stdcall*callback)(UI::IElement*));
	};
}
