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
		private:
			void __draw(ID3D11DeviceContext* pContext) override;
		public:
			UINT size() override
			{
				return 5;
			}
			Panel(Render::Position position, float r, float g, float b);

			void init(Application::Render::Scene* pScene) override;
			IElement* set_pos(float x, float y) override;
			IElement* set_color(float r, float g, float b) override;
		};
	}

}
