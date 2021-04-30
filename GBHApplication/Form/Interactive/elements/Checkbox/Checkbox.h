#pragma once
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{
		class Checkbox : InteractiveElement
		{
		private:
			void __draw(ID3D11DeviceContext* pContext, ID3D11Device* pDevice) override;
			Render::Resolution resolution;
			Render::Color color;
		public:

			UINT size() override;
			
			EventCallback onChange = default_event_callback;

			Checkbox(Render::Position position,Render::Resolution resolution, Render::Color color);
			void init(Application::InteractiveForm* pForm) override;

			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;

			bool point_belongs(POINT point) override;

			void move_by(float x, float y) override;
		};
	}
}
