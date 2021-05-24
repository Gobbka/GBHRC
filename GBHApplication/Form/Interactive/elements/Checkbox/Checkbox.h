#pragma once
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{
		class Checkbox : public InteractiveElement
		{
		private:
			void draw(Render::DrawEvent*event) override;
			Render::Resolution resolution;
			Render::Color color;

			bool checked = false;
		public:
			Render::Color active_color { 0.27f,0.73f,0.39f };
			Render::Color non_active_color{ 0.305f,0.305f,0.305f };
		public:

			bool is_checked();
			
			UINT size() override;
			
			EventCallback onChange = default_event_callback;

			Checkbox(Render::Position position,Render::Resolution resolution, Render::Color color);
			void init() override;

			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;

			bool point_belongs(Render::Position point) override;

			void move_by(float x, float y) override;

			void handle_mouse_up() override;
		};
	}
}
