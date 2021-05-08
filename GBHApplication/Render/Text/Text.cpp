#include "Text.h"
#include "../Engine/Engine.h"

Application::Render::Text::Text(DirectX::SpriteFont* font, TextAlign text_align, Position pos)
{
	this->font = font;
	this->text_align = text_align;
	this->color = { 1,1,1 };
}

Application::Render::Text::~Text()
{
	delete this->font;
}

void Application::Render::Text::set_text(const char* text)
{
	this->text = text;
	auto rect = this->font->MeasureDrawBounds(text, DirectX::XMFLOAT2{ 0, 0 });
	this->text_resolution = { (UINT)rect.right,(UINT)rect.bottom };
}

void Application::Render::Text::DrawInRect(Render::Engine* engine, Render::Position position)
{
	auto* batch = engine->get_batch();
	batch->Begin();
	auto center_pos = Application::point_to_center(position);
	auto scale = 1.f;

	if (this->limitRect.width != 0 || this->limitRect.height != 0)
	{
		auto font_rect = this->text_resolution;
		float width_scale = limitRect.width / font_rect.width;
		float height_scale = limitRect.height / font_rect.height;
		scale = min(width_scale, height_scale);

		if (this->text_align == TextAlign::Center)
		{
			center_pos.x += limitRect.width / 2 - font_rect.width / 2;
			center_pos.y -= limitRect.height / 2;
		}
	}

	this->font->DrawString(
		batch,
		this->text,
		DirectX::XMFLOAT2{center_pos.x, center_pos.y},
		{ color.r,color.g,color.b },
		0,
		DirectX::XMFLOAT2{ 0,0 },
		scale
	);

	batch->End();
}

// auto* batch = engine->get_batch();
// batch->Begin();
// auto font_rect = this->font->MeasureDrawBounds(this->text, DirectX::XMFLOAT2{ 0,0 });
// float width_scale = limitRect.width / font_rect.right;
// float height_scale = limitRect.height / font_rect.bottom;
// const auto final_scale = min(width_scale, height_scale);
   
// auto center_pos = Application::point_to_center(position);
// center_pos = { center_pos.x + position.x,center_pos.y + position.y };
// 
// if(this->text_align == TextAlign::Center)
// {
// 	center_pos.x += limitRect.width / 2 - font_rect.right/2;
// 	center_pos.y -= limitRect.height / 2;
// }
// 
// this->font->DrawString(
// 	batch,
// 	this->text,
// 	DirectX::XMFLOAT2{center_pos.x, center_pos.y},
// 	{ color.r,color.g,color.b },
// 	0,
// 	DirectX::XMFLOAT2{ 0,0 },
// 	final_scale
// );
// 
// batch->End();
