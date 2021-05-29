#include "rectangle.h"
#include "../../../../Managers/RectangleManager.h"
#include "../../../../Render/Engine/Engine.h"

using namespace Application::Render;

void Application::Canvas::Rectangle::init()
{

	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);
}

Application::Canvas::Rectangle::Rectangle(Position pos, Resolution res, Color col)
{
	this->position = pos;
	this->resolution = res;
	this->color = col;
}

void Application::Canvas::Rectangle::move_by(float x, float y)
{
	CanvasElement::move_by(x, y);
}

void Application::Canvas::Rectangle::draw(Render::D3D11DrawEvent* event)
{
	auto* p_context = event->get_context();

	if (!this->render)
		return;

	if (this->wireframed == false)
	{
		event->draw(4);
		p_context->Draw(4, this->index);
		return;
	}

	static ID3D11RasterizerState* state;
	if (state == nullptr)
	{
		D3D11_RASTERIZER_DESC rDesc{};
		rDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rDesc.CullMode = D3D11_CULL_NONE;
		rDesc.DepthClipEnable = true;
		event->engine->pDevice->CreateRasterizerState(&rDesc, &state);
	}
	p_context->RSSetState(state);
	event->draw(4);
	p_context->RSSetState(event->old_state);
}

void Application::Canvas::Rectangle::set_pos(float x, float y)
{
	Managers::Rectangle::set_rect(this->get_ptr(), x, y, resolution.width, resolution.height);
	this->position = { x,y };
}

void Application::Canvas::Rectangle::set_color(float r, float g, float b)
{
	Managers::Rectangle::set_color(this->get_ptr(), r, g, b );
	this->color = { r,g,b };
}

void Application::Canvas::Rectangle::set_resolution(UINT width, UINT height)
{
	Managers::Rectangle::set_rect(this->get_ptr(), this->position.x, this->position.y, width, height);
	this->resolution = { width,height };
}

UINT Application::Canvas::Rectangle::size()
{
	return 4;
}


Resolution Application::Canvas::Rectangle::get_resolution() const
{
	return this->resolution;
}
