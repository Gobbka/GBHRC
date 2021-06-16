#include "Button.h"
#include "../../InteractiveForm.h"
#include "../../../../Render/Engine/Engine.h"
#include "../Label/Label.h"

void Application::UI::Button::draw(Render::DrawEvent* event)
{
	event->draw_element(&this->back_rect);
	this->text.draw(event);
}

Application::UI::Button::Button(Render::Position position, Render::Resolution resolution, Render::Color color, DirectX::SpriteFont* font,
                                const char* text)
		: back_rect(position,resolution,color),
			text(position,text,font,{1,1,1}),
		non_active_color(color)
{
	this->text.limitRect = resolution;	
	this->text.set_text(text);
}

bool Application::UI::Button::point_belongs(Render::Position point)
{
	auto position = back_rect.get_position();
	auto resolution = back_rect.get_resolution();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}


void Application::UI::Button::set_pos(float x, float y)
{
	//Managers::Rectangle::set_rect(this->get_ptr(), x, y, this->resolution.width, this->resolution.height);
	//this->position = { x,y };
	//this->text.set_pos(x, y);
}

void Application::UI::Button::set_temp_color(Render::Color color)
{
	back_rect.set_color(color);
}

Application::UI::ElementDescription Application::UI::Button::get_desc()
{
	return { true,"BUTTON" };
}

void Application::UI::Button::set_color(Render::Color color)
{
	this->non_active_color = color;
	this->set_temp_color(color);
}

void Application::UI::Button::move_by(float x, float y)
{
	this->back_rect.move_by(x, y);
	this->text.move_by(x, y);
}

Application::UI::InteractiveElement* Application::UI::Button::set_resolution(float width, float height)
{
	this->back_rect.set_resolution(width, height);
	this->text.limitRect = { (UINT)width,(UINT)height };
	return this;
}

Application::Render::Resolution Application::UI::Button::get_resolution()
{
	return this->back_rect.get_resolution();
}

void Application::UI::Button::handle_mouse_up()
{
	this->onClick(this);
	this->handle_mouse_enter();
	InteractiveElement::handle_mouse_up();
}

void Application::UI::Button::handle_mouse_down()
{
	this->set_temp_color({ this->non_active_color.r + .2f, non_active_color.g + 0.2f, non_active_color.b + 0.2f });
	InteractiveElement::handle_mouse_down();
}

void Application::UI::Button::handle_mouse_enter()
{
	this->set_temp_color({ this->non_active_color.r + .1f, non_active_color.g + 0.1f, non_active_color.b + 0.1f });
	InteractiveElement::handle_mouse_enter();
}

void Application::UI::Button::handle_mouse_leave()
{
	this->set_temp_color({this->non_active_color.r, non_active_color.g, non_active_color.b});
	InteractiveElement::handle_mouse_leave();
}

Application::Render::Position Application::UI::Button::get_position()
{
	return this->back_rect.get_position();
}

void Application::UI::Button::on_initialize()
{
	this->pForm->add_canvas_element(&this->back_rect);
	this->text.initialize(this->pForm);
}
