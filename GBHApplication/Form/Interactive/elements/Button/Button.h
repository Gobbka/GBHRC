#pragma once
#include "../../../../Render/Render.h"

#include "../IElement/InteractiveElement.h"
#include "../Label/Label.h"


namespace DirectX {
	class SpriteFont;
}

namespace Application {
	namespace Render {
		class Engine;
	}

	class InteractiveForm;
}

namespace Application
{
	namespace UI
	{

		class Button final : public InteractiveElement
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		private:
			void draw(Render::DrawEvent* event) override;
		public:
			Render::Color non_active_color;
			
			UI::Label text;
			
			UINT size() override
			{
				return 4;
			}
			Button(Render::Position position, Render::Resolution resolution, Render::Color color,DirectX::SpriteFont*font,const char*text);

			bool point_belongs(POINT point) override;
			void init() override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_rect(float width, float height);

			Render::Resolution get_resolution();

			EventCallback onClick = default_event_callback;

			void handle_mouse_up() override;
			void handle_mouse_down() override;
			void handle_mouse_enter() override;
			void handle_mouse_leave() override;
		};
	}

}
