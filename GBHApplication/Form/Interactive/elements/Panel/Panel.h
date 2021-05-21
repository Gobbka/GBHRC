#pragma once
#include "../IElement/Parentable.h"

namespace Application
{
	namespace UI
	{
		
		class Panel final : public UI::Parent
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		private:
			void draw(Render::DrawEvent*event) override;
		public:
			UINT size() override
			{
				return 5 + Parent::size();
			}
			Panel(Render::Position position,Render::Resolution resolution, Render::Color color);
			
			bool point_belongs(POINT point) override;
			void init() override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_rect(float width, float height);

			Render::Resolution get_resolution();
		};
	}

}
