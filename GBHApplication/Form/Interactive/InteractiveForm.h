#pragma once
#include "../../Application.h"
#include "../../../GBHRC/CheatApi/GBHRC/gbhrc.h"
#include "../../Render/Scene/CanvasScene.h"
#include "Events/WinIntEventHandler.h"

namespace Application
{

	namespace UI {
		class InteractiveElement;
	}

	class InteractiveForm final : public Render::CanvasScene,public OS_EVENT_HANDLER
	{
	private:
		//void draw_element(Render::IRenderObject* obj, Render::DrawEvent* event) override;
	public:
		struct DragStruct
		{
			POINT dragged_offset;
			UI::InteractiveElement* element;
		};
	private:
		std::vector<UI::InteractiveElement*> interactive_elements;
		void render_components(Render::D3D11DrawEvent* event) override;
		DragStruct* dragged = nullptr;
	public:
		void drag_move(UI::InteractiveElement* element);
		void free_drag_move();

		void initialize_components(Render::Engine* pEngine) override;

		InteractiveForm* add_element(UI::InteractiveElement* element);
	protected:
		void on_lbmouse_up() override;
		void on_lbmouse_down() override;
		void on_mouse_move(int mx,int my) override;
		void on_mouse_scroll(short direction) override;
	};
}
