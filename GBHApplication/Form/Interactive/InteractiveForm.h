#pragma once
#include "../../Render/Scene/Scene.h"

namespace Application
{
	namespace UI {
		class InteractiveElement;
	}

	class InteractiveForm : public Render::Scene
	{		
	public:
		struct DragStruct
		{
			POINT dragged_offset;
			UI::InteractiveElement* element;
		};
	private:
		DragStruct* dragged = nullptr;
	public:
		void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
		void drag_move(UI::InteractiveElement* element);
		void free_drag_move();

		void update_markup(Render::Engine* pEngine);

		void add_elements(UINT count, UI::InteractiveElement* element...);
		InteractiveForm* add_element(UI::InteractiveElement* element);
	};
}
