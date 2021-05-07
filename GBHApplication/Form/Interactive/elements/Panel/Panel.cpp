#include "Panel.h"
#include "../../../../Render/Engine/Engine.h"
#include "../../InteractiveForm.h"
#include "../../../../Managers/RectangleManager.h"

void Application::UI::Panel::__draw(Render::Engine* engine)
{
	engine->pDevContext->Draw(5, this->__index);
	Parent::__draw(engine);
}

Application::UI::Panel::Panel(Render::Position position, Render::Resolution resolution, Render::Color color)
{
	this->color = color;
	this->position = position;
	this->resolution = resolution;
}

bool Application::UI::Panel::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Panel::init(Application::InteractiveForm* pForm)
{
	this->pForm = pForm;

	Parent::set_index_offset(5);
	Parent::init(pForm);

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

Application::UI::InteractiveElement* Application::UI::Panel::set_rect(float width, float height)
{
	auto x = this->position.x;
	auto y = this->position.y;

	Managers::Rectangle::set_rect(this -> get_ptr(), x, y, width, height);
	Managers::Rectangle::set_rect(this->get_ptr(),
		position.x,
		position.y,
		width,
		height
	);
	this->resolution = { (UINT)width,(UINT)height };

	return this;
}
