#include "Button.h"
#include "../../../../Render/Engine/Engine.h"
#include "../Label/Label.h"

void Application::UI::Button::draw(Render::DrawEvent* event)
{
	event->get_context()->Draw(5, this->__index);
}


Application::UI::Button::Button(Render::Position position, Render::Resolution resolution, Render::Color color, DirectX::SpriteFont* font,
                                const char* text)
		: text(position,text,font,{1,1,1})
{
	this->position = position;
	this->non_active_color = color;
	this->color = color;
	this->resolution = resolution;

	this->text.limitRect = resolution;	
	this->text.set_text(text);
}

bool Application::UI::Button::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Button::init(Application::InteractiveForm* pForm)
{
	this->set_pForm(pForm);
	this->text.init(pForm);
	
	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);
}

void Application::UI::Button::set_pos(float x, float y)
{
	Managers::Rectangle::set_rect(this->get_ptr(), x, y, this->resolution.width, this->resolution.height);
	this->position = { x,y };
	this->text.set_pos(x, y);
}

void Application::UI::Button::set_color(float r, float g, float b)
{
	Managers::Rectangle::set_color(this->get_ptr(), r, g, b);
}

void Application::UI::Button::move_by(float x, float y)
{
	Managers::Rectangle::set_rect(this->get_ptr(),
		position.x + x,
		position.y + y,
		resolution.width,
		resolution.height
	);

	this->position.x += x;
	this->position.y += y;

	this->text.move_by(x, y);
}

Application::UI::InteractiveElement* Application::UI::Button::set_rect(float width, float height)
{
	auto x = this->position.x;
	auto y = this->position.y;

	Managers::Rectangle::set_rect(this->get_ptr(), x, y, width, height);
	Managers::Rectangle::set_rect(this->get_ptr(),
		position.x,
		position.y,
		width,
		height
	);
	this->text.limitRect = { (UINT)width,(UINT)height };
	this->resolution = { (UINT)width,(UINT)height };

	return this;
}

Application::Render::Resolution Application::UI::Button::get_resolution()
{
	return this->resolution;
}

void Application::UI::Button::handle_mouse_up()
{
	this->onClick(this);
	InteractiveElement::handle_mouse_up();
}

void Application::UI::Button::handle_mouse_enter()
{
	this->set_color(this->non_active_color.r+10, non_active_color.g+10, non_active_color.b+10);
	InteractiveElement::handle_mouse_enter();
}

void Application::UI::Button::handle_mouse_leave()
{
	this->set_color(this->non_active_color.r, non_active_color.g, non_active_color.b);
	InteractiveElement::handle_mouse_leave();
}


