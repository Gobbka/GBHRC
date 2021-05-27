#include "Panel.h"
#include "../../../../Render/Engine/Engine.h"
#include "../../InteractiveForm.h"
#include "../../../../Managers/RectangleManager.h"

void Application::UI::Panel::draw(Render::DrawEvent* event)
{
	if(this->styles.overflow==VISIBLE_STATE_HIDDEN)
	{
		auto* mask = event->engine->get_mask();
		mask->set_draw_mask();
		event->draw(4);
		mask->set_discard_mask();
	}else
	{
		event->draw(4);
	}

	Parent::draw(event);
	
	if (this->styles.overflow == VISIBLE_STATE_HIDDEN)
	{
		auto* mask = event->engine->get_mask();
	
		mask->unset_mask();
	}
	
}

Application::UI::ElementDescription Application::UI::Panel::get_desc()
{
	return { true,"PANEL" };
}

Application::UI::Panel::Panel(Render::Position position, Render::Resolution resolution, Render::Color color)
{
	this->color = color;
	this->position = position;
	this->resolution = resolution;
}

bool Application::UI::Panel::point_belongs(Render::Position point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Panel::init()
{

	Parent::set_index_offset(4);
	Parent::init();

	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);
}

void Application::UI::Panel::set_pos(float x, float y)
{
	Parent::set_pos(x, y);
	Managers::Rectangle::set_rect(this->get_ptr(), x, y, this->resolution.width, this->resolution.height);
	this->position = { x,y };
}

void Application::UI::Panel::set_color(float r, float g, float b)
{
	Managers::Rectangle::set_color(this->get_ptr(), r, g, b);
	this->color = { r,g,b };
}

void Application::UI::Panel::move_by(float x, float y)
{
	Parent::move_by(x, y);

	Managers::Rectangle::set_rect(this->get_ptr(),
		position.x + x,
		position.y + y,
		resolution.width,
		resolution.height
	);
	
	this->position.x += x;
	this->position.y += y;
}


Application::UI::InteractiveElement* Application::UI::Panel::set_resolution(float width, float height)
{
	Managers::Rectangle::set_rect(this->get_ptr(),
		position.x,
		position.y,
		width,
		height
	);
	this->resolution = { (UINT)width,(UINT)height };

	return this;
}

Application::Render::Resolution Application::UI::Panel::get_resolution()
{
	return this->resolution;
}
