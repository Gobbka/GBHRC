#pragma once
#include "../../../Canvas/elements/rectangle/rectangle.h"
#include "../IElement/Parentable.h"


namespace Application
{
	namespace UI
	{
		
		class Panel : public UI::Parent
		{
		protected:
			Canvas::Rectangle rect;
			
			void draw(Render::DrawEvent*event) override;
			void on_initialize() override;
		public:
			ElementDescription get_desc() override;
			
			//UINT size() override
			//{
			//	return 4;// + Parent::size();
			//}
			
			Panel(Render::Position position,Render::Resolution resolution, Render::Color color);
			
			bool point_belongs(Render::Position point) override;
			void set_pos(float x, float y) override;
			void set_color(Render::Color color) override;
			void set_alpha(float alpha);
			void move_by(float x, float y) override;

			Render::Position get_position() override;
			Render::Resolution get_resolution() override;
			InteractiveElement* set_resolution(float width, float height) override;
		};
	}

}
