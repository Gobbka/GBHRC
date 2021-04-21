#pragma once
#include "../../Application.h"

namespace Application
{
	namespace UI
	{
		
		class Panel final : public UI::IElement
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		private:
			void __draw(ID3D11DeviceContext* pContext) override;

			EventCallback old_mouse_move;
			POINT dragged_at;
			
			void DragMove();
			void FreeDragMove();
		public:
			UINT size() override
			{
				return 5;
			}
			Panel(Render::Position position,Render::Resolution resolution, Render::Color color);
			
			bool point_belongs(POINT point) override;
			void init(Application::Render::Scene* pScene) override;
			IElement* set_pos(float x, float y) override;
			IElement* set_color(float r, float g, float b) override;
		};
	}

}