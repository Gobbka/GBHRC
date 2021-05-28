#pragma once
#include "SpriteFont.h"
#include "../Render.h"
#include "../Scene/IRenderObject.h"

namespace Application
{
	namespace Render
	{

		enum class TextAlign : __int8
		{
			Center = 0x0,
			Left = 0x1,
			Right = 0x2
		};
		
		class Text
		{
		private:
			DirectX::SpriteFont* font;
			const char* text;
			Render::Resolution text_resolution;
		public:
			bool wchar = false;
			
			TextAlign text_align;
			Render::Color color;
			Render::Resolution limitRect;
			
		public:
			Text(DirectX::SpriteFont* font, TextAlign text_align);
			~Text();

			void set_font(DirectX::SpriteFont* font);
			void set_text(const char*text);
			void set_text(const wchar_t*text);

			char* get_text();

			Render::Resolution get_resolution();
			
			void DrawInRect(Render::D3D11DrawEvent* event,Render::Position pos,bool scale=false) const;
		};
	}
}
