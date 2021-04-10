#include "Checkbox.h"

void Application::UI::Checkbox::__draw(ID3D11DeviceContext* pContext)
{
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pContext->Draw(5, this->index);
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->Draw(5, this->index + 5);
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

void Application::UI::Checkbox::init(Render::Scene* pScene)
{
	this->pScene = pScene;
	
	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);

	auto* ptr = this->get_ptr();

	Managers::Rectangle::set_color(ptr, 0.819f, 0.819f, 0.819f);
}

Application::UI::IElement* Application::UI::Checkbox::set_pos(float x, float y)
{
	auto* ptr = this->get_ptr();
	
	Managers::Rectangle::set_rect(ptr, x, y, resolution.width, resolution.height);
	Managers::Rectangle::set_rect(ptr + 5, x + 4, y - 5, resolution.width - 9, resolution.height - 9);
	return this;
}

Application::UI::IElement* Application::UI::Checkbox::set_color(float r, float g, float b)
{
	Managers::Rectangle::set_color(this->get_ptr()+5, r, g, b);
	return this;
}

bool Application::UI::Checkbox::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}
