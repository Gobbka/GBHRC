#pragma once
#include "../../../../Render/Render.h"
#include "../../../Canvas/elements/rectangle/rectangle.h"

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
			void draw(Render::DrawEvent* event) override;
			void set_temp_color(float r, float g, float b);

		private:
			Canvas::Rectangle back_rect;
		public:
			UI::Label text;

			Render::Color non_active_color;

			ElementDescription get_desc() override;

			Button(Render::Position position, Render::Resolution resolution, Render::Color color,DirectX::SpriteFont*font,const char*text);

			bool point_belongs(Render::Position point) override;

			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_resolution(float width, float height) override;

			Render::Resolution get_resolution() override;
			Render::Position get_position() override;
			void add_elements(Render::CanvasScene* scene) override;

			EventCallback onClick = default_event_callback;

			void handle_mouse_up() override;
			void handle_mouse_down() override;
			void handle_mouse_enter() override;
			void handle_mouse_leave() override;
		};
	}

}
