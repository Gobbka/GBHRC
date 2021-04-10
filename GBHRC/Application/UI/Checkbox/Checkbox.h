#pragma once
#include "../../Application.h"
namespace Application
{
	namespace UI
	{
		class Checkbox : Application::UI::IElement
		{
		private:
			void __draw(ID3D11DeviceContext* pContext) override;
			Render::Resolution resolution;
			Render::Color color;
		public:

			UINT size() override;
			
			EventCallback onChange = default_event_callback;

			Checkbox(Render::Position position,Render::Resolution resolution, Render::Color color);
			void init(Render::Scene* pScene) override;

			UI::IElement* set_pos(float x, float y) override;
			UI::IElement* set_color(float r, float g, float b) override;

			bool point_belongs(POINT point) override;
		};
	}
}