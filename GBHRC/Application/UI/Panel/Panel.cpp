#include "Panel.h"

void Application::UI::Panel::__draw(ID3D11DeviceContext* pContext)
{
	pContext->Draw(5, this->index);
}

Application::UI::Panel::Panel(Render::Position position, float r, float g, float b)
{
	this->init_values = new Panel::InitValues{ r,g,b };
	this->position = position;
}

void Application::UI::Panel::init(Application::Render::Scene* pScene)
{
	this->pScene = pScene;

	this->set_pos(position.x, position.y);
	this->set_color(init_values->r, init_values->g, init_values->b);

	delete this->init_values;
}

Application::UI::IElement* Application::UI::Panel::set_pos(float x, float y)
{
	const auto height = position.height;
	const auto width = position.width;
	auto* ptr = this->get_ptr();

	ptr[0].pos = DirectX::XMFLOAT3(x, y, 1.f);
	ptr[1].pos = DirectX::XMFLOAT3(x, y - height, 1.f);
	ptr[2].pos = DirectX::XMFLOAT3(x + width, y - height, 1.f);
	ptr[3].pos = DirectX::XMFLOAT3(x + width, y, 1.f);
	ptr[4].pos = DirectX::XMFLOAT3(x, y, 1.f);
	return this;
}

Application::UI::IElement* Application::UI::Panel::set_color(float r, float g, float b)
{
	auto* ptr = this->get_ptr();
	for (int i = 0; i < 5; i++)
		ptr[i].color = DirectX::XMFLOAT4(r, g, b, 1.f);

	return this;
}
