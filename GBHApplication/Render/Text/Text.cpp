#include "Text.h"
#include "../Engine/Engine.h"

Application::Render::Text::Text(DirectX::SpriteFont* font, TextAlign text_align)
{
	this->font = font;
	this->text_align = text_align;
	this->color = { 1,1,1 };
	this->limitRect = { 0,0 };
	this->text = nullptr;
	this->text_resolution = { 0,0 };
}

Application::Render::Text::~Text()
{
	delete this->font;
}

void Application::Render::Text::set_font(DirectX::SpriteFont* font)
{
	this->font = font;
}

void Application::Render::Text::set_text(const char* text)
{
	this->text = text;
	RECT rect= this->font->MeasureDrawBounds(text, DirectX::XMFLOAT2{ 0, 0 });;
	this->wchar = false;
	this->text_resolution = { (UINT)rect.right,(UINT)rect.bottom };
}

void Application::Render::Text::set_text(const wchar_t* text)
{
	this->text = (const char*)text;
	this->wchar = true;
	auto rect = this->font->MeasureDrawBounds((wchar_t*)text, DirectX::XMFLOAT2{ 0, 0 });
	this->text_resolution = { (UINT)rect.right,(UINT)rect.bottom };
}

char* Application::Render::Text::get_text()
{
	return (char*)this->text;
}

Application::Render::Resolution Application::Render::Text::get_resolution()
{
	return this->text_resolution;
}

void Application::Render::Text::DrawInRect(Render::D3D11DrawEvent* event, Render::Position position,bool scalable) const
{
	auto* batch = event->engine->get_batch();
	auto* mask = event->engine->get_mask();
	// DirectX::SpriteSortMode_Deferred,nullptr,nullptr,mask->get_current_state()
	batch->Begin();
	auto center_pos = Application::point_to_center(position);
	auto scale = 1.f;
	
	// center calculations with scale is broken
	// so TODO: fix it
	if (this->limitRect.width != 0 || this->limitRect.height != 0)
	{
		auto font_rect = this->text_resolution;

		float width_scale = (float)limitRect.width / (float)font_rect.width;
		float height_scale = (float)limitRect.height / (float)font_rect.height;
		
		if(scalable)
		{
			scale = min(width_scale, height_scale);
		}else
		{
			scale = min(scale, width_scale);
			scale = min(scale, height_scale);
		}

		if (this->text_align == TextAlign::Center)
		{
			center_pos.x += limitRect.width / 2 - font_rect.width / 2;
			center_pos.y += limitRect.height / 2 - font_rect.height / 2;
		}
	}

	if(this->wchar)	
		this->font->DrawString(
			batch,
			(wchar_t*)this->text,
			DirectX::XMFLOAT2{center_pos.x, center_pos.y},
			{ color.r,color.g,color.b },
			0,
			DirectX::XMFLOAT2{ 0,0 },
			scale
		);
	else
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
	
	event->reset_render_state();
	mask->reset_mask();
}
