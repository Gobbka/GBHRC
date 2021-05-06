#pragma once
#include "SpriteFont.h"
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{

		class Label final : public InteractiveElement
		{
		private:
			Render::Color color;
			Render::Resolution resolution;
			char* _text;
			DirectX::SpriteFont* font;
		private:
			void __draw(Render::Engine* engine) override;
		public:
			UINT size() override
			{
				return 0;
			}
			Label(Render::Position position, const char* text,DirectX::SpriteFont*font, Render::Color color);

			void set_text(char* text);
			bool point_belongs(POINT point) override;
			void init(Application::InteractiveForm* pForm) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
		};
	}

}