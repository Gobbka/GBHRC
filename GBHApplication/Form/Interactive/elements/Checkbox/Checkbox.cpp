#include "Checkbox.h"
#include "../../../../Managers/RectangleManager.h"
#include "../../../../Render/Engine/Engine.h"

void Application::UI::Checkbox::__draw(Render::Engine*engine)
{
	auto* pContext = engine->pDevContext;
	
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pContext->Draw(5, this->__index);
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->Draw(5, this->__index+5);
}

bool Application::UI::Checkbox::is_checked()
{
	return this->checked;
}

UINT Application::UI::Checkbox::size()
{
	return 10;
}

Application::UI::Checkbox::Checkbox(Render::Position position, Render::Resolution resolution, Render::Color color)
{
	this->position = position;
	this->resolution = resolution;
	this->color = color;
}

void Application::UI::Checkbox::init(Application::InteractiveForm* pForm)
{
	this->pForm = pForm;
	
	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);

	auto* ptr = this->get_ptr();

	Managers::Rectangle::set_color(ptr, 0.819f, 0.819f, 0.819f);
}

void Application::UI::Checkbox::set_pos(float x, float y)
{
	auto* ptr = this->get_ptr();
	
	Managers::Rectangle::set_rect(ptr, x, y, resolution.width, resolution.height);
	Managers::Rectangle::set_rect(ptr + 5, x + 4, y - 4, resolution.width - 8, resolution.height - 8);
}

void Application::UI::Checkbox::set_color(float r, float g, float b)
{
	Managers::Rectangle::set_color(this->get_ptr()+5, r, g, b);
}

bool Application::UI::Checkbox::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Checkbox::move_by(float x, float y)
{
	DEBUG_LOG("CHECKBOX MOVE: " << x << " " << y << this->__index);
	InteractiveElement::move_by(x, y);
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
