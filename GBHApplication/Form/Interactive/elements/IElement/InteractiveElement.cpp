#include "InteractiveElement.h"
#include "../../InteractiveForm.h"

Application::UI::ElementDescription::ElementDescription(bool has_children, const char* string_name)
{
	this->has_children = has_children;
	this->string_name = string_name;
}

void Application::UI::InteractiveElement::set_margin(float x, float y)
{
	this->styles.margin.x = this->styles.margin.z = x;
	this->styles.margin.y = this->styles.margin.w = y;
}

void Application::UI::InteractiveElement::set_margin(float x, float y, float z, float w)
{
	this->styles.margin = { x,y,z,w };
}

void Application::UI::InteractiveElement::initialize(InteractiveForm* form)
{
	this->pForm = form;
	this->on_initialize();
}

//void Application::UI::InteractiveElement::move_by(float x, float y)
//{
//	
//	const auto size = this->size();
//	GVertex::Vertex* ptr = this->get_ptr();
//	for (UINT i = 0; i < size; i++)
//	{
//		const auto pos = ptr[i].pos;
//		ptr[i].pos = DirectX::XMFLOAT3(pos.x + x, pos.y + y, 1.f);
//	}
//
//	this->position.x += x;
//	this->position.y += y;
//}

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
	this->state.hovered = false;
	this->onMouseLeave(this);
}

void Application::UI::InteractiveElement::handle_mouse_enter()
{
	this->state.hovered = true;
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

void Application::UI::InteractiveElement::handle_mouse_scroll(int delta)
{
	this->onMouseScroll(this, delta);
}

