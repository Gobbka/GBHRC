#pragma once
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{
		
		class Panel final : public UI::InteractiveElement
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		private:
			void __draw(ID3D11DeviceContext* pContext, ID3D11Device* pDevice) override;
		public:
			UINT size() override
			{
				return 5;
			}
			Panel(Render::Position position,Render::Resolution resolution, Render::Color color);
			
			bool point_belongs(POINT point) override;
			void init(Application::InteractiveForm* pForm) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_rect(float width, float height);
		};
	}

}
