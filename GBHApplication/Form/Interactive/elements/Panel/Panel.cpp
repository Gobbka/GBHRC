#include "Panel.h"
#include "../../InteractiveForm.h"
#include "../../../../Managers/RectangleManager.h"

void Application::UI::Panel::__draw(ID3D11DeviceContext* pContext, ID3D11Device* pDevice)
{
	pContext->Draw(5, this->__index);
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

	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);

	Parent::init(pForm);
}

void Application::UI::Panel::set_pos(float x, float y)
{
	Parent::set_pos(x, y);

	this->position = { x,y };
}

void Application::UI::Panel::set_color(float r, float g, float b)
{
	Parent::set_color(r, g, b);
	this->color = { r,g,b };
}

void Application::UI::Panel::move_by(float x, float y)
{
	Parent::move_by(x, y);
	this->position.x += x;
	this->position.y += y;
}

Application::UI::InteractiveElement* Application::UI::Panel::set_rect(float width, float height)
{
	auto x = this->position.x;
	auto y = this->position.y;

	Managers::Rectangle::set_rect(this -> get_ptr(), x, y, width, height);

	this->resolution = { (UINT)width,(UINT)height };

	return this;
}
