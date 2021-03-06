#pragma once
#include "../IElement/CanvasElement.h"
namespace Application
{
	namespace Canvas
	{
		class Rectangle : public Canvas::CanvasElement
		{
		private:
			Render::Resolution resolution;
			Render::Color4 color;

			void init() override;
		public:
			bool wireframed = false;
			
			Rectangle(Render::Position pos, Render::Resolution res, Render::Color4 col);

			void move_by(float x, float y) override;
			void draw(Render::D3D11DrawEvent*engine) override;
			void set_pos(float x, float y) override;
			void set_color(Render::Color4 color) override;
			void set_alpha(float alpha);
			void set_resolution(UINT width, UINT height);
			UINT size() override;

			Render::Resolution get_resolution() const;
		};
	}
}
