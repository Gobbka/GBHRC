#include "CanvasElement.h"
#include "../../../../Render/Scene/CanvasScene.h"

Application::Render::Position Application::Canvas::CanvasElement::get_position() const
{
	return this->position;
}

void Application::Canvas::CanvasElement::move_by(float x, float y)
{
	const auto size = this->size();
	GVertex::Vertex* ptr = this->get_ptr();
	for (UINT i = 0; i < size; i++)
	{
		const auto pos = ptr[i].pos;
		ptr[i].pos = DirectX::XMFLOAT3(pos.x + x, pos.y + y, 1.f);
	}

	this->position.x += x;
	this->position.y += y;
}

void Application::Canvas::CanvasElement::initialize(Render::CanvasScene* pForm)
{
	this->canvas_scene = pForm;
	this->init();
}

GVertex::Vertex* Application::Canvas::CanvasElement::get_ptr() const
{
	return this->canvas_scene->canvas()->get_ptr() + this->index;
}
