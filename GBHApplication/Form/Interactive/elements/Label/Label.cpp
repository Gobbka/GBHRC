#include "Label.h"
#include "../../../../Render/Engine/Engine.h"
#include "../../InteractiveForm.h"

void Application::UI::Label::draw(Render::DrawEvent* event)
{
	Text::DrawInRect(event, this->position,this->scalable);
}

Application::UI::Label::Label(Render::Position position, const char* text, DirectX::SpriteFont* font, Render::Color color)
	: Text(font,Render::TextAlign::Center)
{	
	Text::set_text(text);
	Text::color = color;
	this->position = position;
}

Application::UI::Label::Label(Render::Position position, const char* text, DirectX::SpriteFont* font,
	Render::Color color, Render::Resolution limitResolution)
	: Text(font, Render::TextAlign::Center)
{
	Text::set_text(text);
	Text::limitRect = limitResolution;
	Text::color = color;
	this->position = position;
}

bool Application::UI::Label::point_belongs(POINT point)
{
	// TODO: make
	return false;
}

void Application::UI::Label::set_pos(float x, float y)
{
	this->position = { x, y };
}

void Application::UI::Label::set_color(float r, float g, float b)
{
	this->color = { r,g,b };
}

void Application::UI::Label::move_by(float x, float y)
{
	this->position = {
		x + position.x,
		position.y + y
	};
}

