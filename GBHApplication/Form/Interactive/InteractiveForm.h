#pragma once
#include "../../Render/Scene/Scene.h"

namespace Application
{
	namespace UI {
		class IElement;
	}

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

		void add_elements(UINT count, UI::IElement* element...);
	};
}
