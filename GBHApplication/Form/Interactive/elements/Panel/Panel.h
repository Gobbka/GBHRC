#pragma once
#include "../IElement/Parentable.h"

namespace Application
{
	namespace UI
	{
		
		class Panel : public UI::Parent
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		protected:
			void draw(Render::DrawEvent*event) override;
		public:
			ElementDescription get_desc() override;
			
			UINT size() override
			{
				return 4 + Parent::size();
			}
			Panel(Render::Position position,Render::Resolution resolution, Render::Color color);
			
			bool point_belongs(Render::Position point) override;
			void init() override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_rect(float width, float height);
			
			Render::Resolution get_resolution() override;
			InteractiveElement* set_resolution(float width, float height) override;
		};
	}

}
