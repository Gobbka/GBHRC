#pragma once
#include "SpriteFont.h"
#include "../../../../Render/Text/Text.h"
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{

		class Label final : public InteractiveElement, public Render::Text
		{
		private:
			Render::Position position;
		public:

			Render::Resolution get_resolution() override;
			
			ElementDescription get_desc() override;
			
			bool scalable = false;
			
			void draw(Render::DrawEvent* event) override;
			
			Label(Render::Position position, const char* text,DirectX::SpriteFont*font, Render::Color color);
			Label(Render::Position position, const char* text,DirectX::SpriteFont*font, Render::Color color, Render::Resolution limitResolution);

			bool point_belongs(Render::Position point) override;

			InteractiveElement* set_resolution(float width, float height) override;
			
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			void move_by(float x, float y) override;
			Render::Position get_position() override;
		};
	}

}