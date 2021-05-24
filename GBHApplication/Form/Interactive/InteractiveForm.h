#pragma once
#include "../../Application.h"
#include "../../Render/Scene/Scene.h"
#include "Events/WinIntEventHandler.h"

namespace Application
{

	namespace UI {
		class InteractiveElement;
	}

	class InteractiveForm final : public Render::Scene,public OS_EVENT_HANDLER
	{
	private:
		void draw_element(Render::IRenderObject* obj, Render::DrawEvent* event) override;
	public:
		struct DragStruct
		{
			POINT dragged_offset;
			UI::InteractiveElement* element;
		};
	private:
		DragStruct* dragged = nullptr;
	public:

		//void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
		void drag_move(UI::InteractiveElement* element);
		void free_drag_move();

		void initialize_components(Render::Engine* pEngine);

		InteractiveForm* add_element(UI::InteractiveElement* element);
	protected:
		void on_lbmouse_up() override;
		void on_lbmouse_down() override;
		void on_mouse_move(int mx,int my) override;
		void on_mouse_scroll(short direction) override;
	};
}
