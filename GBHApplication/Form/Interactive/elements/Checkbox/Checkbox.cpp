#include "Checkbox.h"
#include "../../../../Render/Engine/Engine.h"

void Application::UI::Checkbox::draw(Render::DrawEvent* event)
{
	event->draw_element(&this->rectangle);
}

bool Application::UI::Checkbox::is_checked()
{
	return this->checked;
}

Application::UI::ElementDescription Application::UI::Checkbox::get_desc()
{
	return { false,"CHECKBOX" };
}

void Application::UI::Checkbox::add_elements(Render::CanvasScene* scene)
{
	scene->add_element(&this->rectangle);
}


Application::UI::Checkbox::Checkbox(Render::Position position, Render::Resolution resolution, Render::Color color)
	:rectangle(position,resolution,color)
{
}

void Application::UI::Checkbox::set_pos(float x, float y)
{
	this->rectangle.set_pos(x, y);
}

void Application::UI::Checkbox::set_color(float r, float g, float b)
{
	this->rectangle.set_color(r, g, b);
}

Application::Render::Position Application::UI::Checkbox::get_position()
{
	return this->rectangle.get_position();
}

Application::Render::Resolution Application::UI::Checkbox::get_resolution()
{
	return this->rectangle.get_resolution();
}

Application::UI::InteractiveElement* Application::UI::Checkbox::set_resolution(float width, float height)
{
	this->rectangle.set_resolution(width, height);
	return this;
}

bool Application::UI::Checkbox::point_belongs(Render::Position point)
{
	auto position = this->rectangle.get_position();
	auto resolution = this->rectangle.get_resolution();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Checkbox::move_by(float x, float y)
{
	this->rectangle.move_by(x, y);
}

void Application::UI::Checkbox::handle_mouse_up()
{
	this->checked = !this->checked;
	
	if (this->checked == true)
		this->set_color(active_color.r, active_color.g, active_color.b);
	else
		this->set_color(non_active_color.r, non_active_color.g, non_active_color.b);

	onChange(this);
	InteractiveElement::handle_mouse_up();
}
