#pragma once
#include "../../CanvasForm.h"
#include "../IElement/CanvasElement.h"
namespace Application
{
	namespace Canvas
	{
		class Rectangle : public Canvas::CanvasElement
		{
		private:
			Render::Resolution resolution;
			Render::Color color;

			void init() override;
		public:
			bool wireframed = false;
			
			Rectangle(Render::Position pos, Render::Resolution res, Render::Color col);

			void move_by(float x, float y) override;
			void draw(Render::DrawEvent*engine) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void set_resolution(UINT width, UINT height);
			UINT size() override;

			Render::Resolution get_resolution() const;
		};
	}
}
