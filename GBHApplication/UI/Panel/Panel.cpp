#include "Panel.h"

void Application::UI::Panel::__draw(ID3D11DeviceContext* pContext)
{
	pContext->Draw(5, this->index);
}

void Application::UI::Panel::DragMove()
{
	this->dragged_at = Application::nigger();
	//this->old_mouse_move = this->onMouseMove;
	this->onMouseMove = [](Application::UI::UIElementEventArgs args,float mX,float mY)
	{
		//auto point = Application::nigger();
		//DEBUG_LOG("X: "<< std::dec << point.x << " Y: " << point.y);
		args->set_pos(mX-5, mY+5);
	};
}

void Application::UI::Panel::FreeDragMove()
{
	//this->onMouseMove = old_mouse_move;
}

Application::UI::Panel::Panel(Render::Position position, Render::Resolution resolution, Render::Color color)
{
	this->color = color;
	this->position = position;
	this->resolution = resolution;

	this->onMouseDown = [](UI::UIElementEventArgs args)
	{
		Panel* panel = (Panel * )args;
		panel->DragMove();
	};

	this->onMouseUp = [](UI::UIElementEventArgs args)
	{
		Panel* panel = (Panel*)args;
		panel->FreeDragMove();
	};
}

bool Application::UI::Panel::point_belongs(POINT point)
{
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Panel::init(Render::Scene* pScene)
{
	this->pScene = pScene;

	this->set_pos(position.x, position.y);
	this->set_color(color.r, color.g, color.b);
}

Application::UI::IElement* Application::UI::Panel::set_pos(float x, float y)
{
	const auto height = resolution.height;
	const auto width = resolution.width;
	auto* ptr = this->get_ptr();

	ptr[0].pos = DirectX::XMFLOAT3(x, y, 1.f);
	ptr[1].pos = DirectX::XMFLOAT3(x, y - height, 1.f);
	ptr[2].pos = DirectX::XMFLOAT3(x + width, y - height, 1.f);
	ptr[3].pos = DirectX::XMFLOAT3(x + width, y, 1.f);
	ptr[4].pos = DirectX::XMFLOAT3(x, y, 1.f);

	this->position = { x,y };
	
	return this;
}

Application::UI::IElement* Application::UI::Panel::set_color(float r, float g, float b)
{
	auto* ptr = this->get_ptr();
	for (int i = 0; i < 5; i++)
		ptr[i].color = DirectX::XMFLOAT4(r, g, b, 1.f);

	return this;
}
