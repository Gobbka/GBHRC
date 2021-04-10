#pragma once
#include "../../Application.h"

namespace Application
{
	namespace UI
	{
		
		class Panel final : public UI::IElement
		{
		public:
			struct InitValues
			{
				float r;
				float g;
				float b;
			};
		private:
			InitValues* init_values;
			Render::Resolution resolution;
		private:
			void __draw(ID3D11DeviceContext* pContext) override;
		public:
			UINT size() override
			{
				return 5;
			}
			Panel(Render::Position position,Render::Resolution resolution, float r, float g, float b);

			bool point_belongs(POINT point) override;
			void init(Application::Render::Scene* pScene) override;
			IElement* set_pos(float x, float y) override;
			IElement* set_color(float r, float g, float b) override;
		};
	}

}
