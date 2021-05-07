#include "Label.h"
#include "../../../../Render/Engine/Engine.h"
#include "../../InteractiveForm.h"

void Application::UI::Label::__draw(Render::Engine* engine)
{
	engine->get_batch()->Begin();
	
	this->font->DrawString(engine->get_batch(), 
		this->_text, 
		{ this->position.x,this->position.y }, 
		{ this->color.r,this->color.g,this->color.b }, 
		0.0f,
		DirectX::XMFLOAT2(0.0f, 0.0f),
		DirectX::XMFLOAT2(1.0f, 1.0f)
	);

	engine->get_batch()->End();
}

Application::UI::Label::Label(Render::Position position, const char* text, DirectX::SpriteFont* font, Render::Color color)
{
	this->position = position;
	this->font = font;
	this->color = color;
	
	this->set_text((char*)text);
}

void Application::UI::Label::set_text(char* text)
{
	this->_text = text;
	auto rect = this->font->MeasureDrawBounds(text, { 0,0 ,0});
	this->resolution = { (UINT)rect.right,(UINT)rect.bottom };
}

bool Application::UI::Label::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Label::init(Application::InteractiveForm* pForm)
{
	this->pForm = pForm;
	this->set_pos(position.x, position.y);
}

void Application::UI::Label::set_pos(float x, float y)
{
	auto res = pForm->get_screen_resolution();

	this->position = { x + res.width / 2,y + res.height / 2 };
}

void Application::UI::Label::set_color(float r, float g, float b)
{
	this->color = { r,g,b };
}

void Application::UI::Label::move_by(float x, float y)
{
	this->position = {
		x + position.x,
		y + position.y
	};
}
