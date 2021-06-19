#include "Parentable.h"

#include "../../../../Render/Scene/CanvasScene.h"

void Application::UI::Parent::handle_mouse_up()
{
	for (auto* element : this->childs)
	{
		if (element->state.hovered)
			element->handle_mouse_up();
	}
	InteractiveElement::handle_mouse_up();
}

void Application::UI::Parent::handle_mouse_down()
{
	for(auto*element:this->childs)
	{
		if (element->state.hovered)
			element->handle_mouse_down();
	}
	InteractiveElement::handle_mouse_down();
}

void Application::UI::Parent::handle_mouse_enter()
{
	InteractiveElement::handle_mouse_enter();
}

void Application::UI::Parent::handle_mouse_leave()
{
	for (auto* element : this->childs)
		element->handle_mouse_leave();
	InteractiveElement::handle_mouse_leave();
}

void Application::UI::Parent::handle_mouse_move(float mX, float mY)
{
	const auto length = this->childs.size() - 1;
	bool e_handled = false;

	for (long long i = length; i >= 0; i--)
	{
		auto* element = (UI::InteractiveElement*)this->childs[i];
		
		if (
			e_handled == false &&
			element->state.visible == VisibleState::VISIBLE_STATE_VISIBLE &&
			element->point_belongs({(mX),(mY)})
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(mX,mY);
			e_handled = true;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	InteractiveElement::handle_mouse_move(mX, mY);
}

void Application::UI::Parent::handle_mouse_scroll(int delta)
{
	for (auto* element : this->childs)
	{
		if (element->state.hovered)
			element->handle_mouse_scroll(delta);
	}
	InteractiveElement::handle_mouse_scroll(delta);
}

void Application::UI::Parent::on_initialize()
{
	this->foreach([this](InteractiveElement* element)
		{
			element->initialize(this->form);
			element->move_by(this->offset_position.x, this->offset_position.y);
		});

	this->initialized = true;
}

Application::UI::Parent::Parent(Render::Position position)
{
	this->offset_position = position;
}

void Application::UI::Parent::draw(Render::DrawEvent* event)
{
	for (auto* element : this->childs)
		if (element->state.visible == VisibleState::VISIBLE_STATE_VISIBLE)
			element->draw(event);
}

void Application::UI::Parent::set_color(Render::Color color)
{
	for (auto* element : this->childs)
		element->set_color(color);
}

void Application::UI::Parent::move_by(float x, float y)
{
	for (auto* element : this->childs)
		element->move_by(x,y);
}

//void Application::UI::Parent::init()
//{
//	for (auto* element : this->elements)
//	{
//		element->initialize(this->pForm);
//	}
//}

void Application::UI::Parent::foreach(std::function<void(InteractiveElement* element)> iterator)
{
	for (auto* element : childs)
	{
		iterator(element);
	}
}

Application::UI::InteractiveElement* Application::UI::Parent::element_at(UINT index)
{
	return this->childs[index];
}

Application::UI::Parent* Application::UI::Parent::add_element(InteractiveElement* element)
{
	if(element->get_parent()!=nullptr)
		return this;
	
	this->childs.push_back(element);
	if(this->initialized)
	{
		element->initialize(this->form);
		auto pos = this->get_position();
		element->move_by(pos.x, pos.y);
	}
	return this;
}

Application::UI::Parent* Application::UI::Parent::add_element(InteractiveElement* element, bool visible)
{
	element->state.visible = (VisibleState) !element->state.visible;
	element->set_parent(this);
	return this->add_element(element);
}

