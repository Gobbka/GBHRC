#pragma once
#include "../../../../Render/Render.h"

#include "../IElement/InteractiveElement.h"
#include "../Label/Label.h"


namespace DirectX {
	class SpriteFont;
}

namespace Application {
	namespace Render {
		class Engine;
	}

	class InteractiveForm;
}

namespace Application
{
	namespace UI
	{

		class Button final : public InteractiveElement
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
		private:
			void __draw(Render::Engine* engine) override;
		public:
			UI::Label text;
			
			UINT size() override
			{
				return 5;
			}
			Button(Render::Position position, Render::Resolution resolution, Render::Color color,DirectX::SpriteFont*font,const char*text);

			bool point_belongs(POINT point) override;
			void init(Application::InteractiveForm* pForm) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			UI::InteractiveElement* set_rect(float width, float height);

			Render::Resolution get_resolution();
		};
	}

}
