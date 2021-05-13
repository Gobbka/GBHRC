#include "InteractiveElement.h"
#include "../../InteractiveForm.h"

Application::Render::Position Application::UI::InteractiveElement::get_position() const
{
	return this->position;
}

void Application::UI::InteractiveElement::move_by(float x, float y)
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

GVertex::Vertex* Application::UI::InteractiveElement::get_ptr() const
{
	return this->pForm->get_ptr() + this->__index;
}

Application::UI::Parent* Application::UI::InteractiveElement::get_parent() const
{
	return this->_parent;
}

Application::InteractiveForm* Application::UI::InteractiveElement::get_form() const
{
	return this->pForm;
}


//============================\\
//  EVENT'S HANDLER'S
//
//

void Application::UI::InteractiveElement::handle_mouse_move( float mX, float mY)
{
	this->onMouseMove(this, mX, mY);
}

void Application::UI::InteractiveElement::handle_mouse_leave()
{
	this->hovered = false;
	this->onMouseLeave(this);
}

void Application::UI::InteractiveElement::handle_mouse_enter()
{
	this->hovered = true;
	this->onMouseEnter(this);
}

void Application::UI::InteractiveElement::handle_mouse_up()
{
	this->onMouseUp(this);
}

void Application::UI::InteractiveElement::handle_mouse_down()
{
	this->onMouseDown(this);
}

