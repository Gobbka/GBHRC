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
		public:
			Rectangle(Render::Position pos, Render::Resolution res, Render::Color col);

			void move_by(float x, float y) override;
			void __draw(ID3D11DeviceContext* p_context, ID3D11Device* pDevice) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			bool point_belongs(POINT point) override;
			UINT size() override;
			void init(Canvas::CanvasForm* pForm) override;
		};
	}
}
