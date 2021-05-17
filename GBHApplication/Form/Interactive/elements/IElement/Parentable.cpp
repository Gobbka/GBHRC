#include "Parentable.h"

#include "../../../../Render/Scene/Scene.h"

void Application::UI::Parent::handle_mouse_up()
{
	for (auto* element : this->elements)
	{
		if (element->hovered)
			element->handle_mouse_up();
	}
	InteractiveElement::handle_mouse_up();
}

void Application::UI::Parent::handle_mouse_down()
{
	for(auto*element:this->elements)
	{
		if (element->hovered)
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
	for (auto* element : this->elements)
		element->handle_mouse_leave();
	InteractiveElement::handle_mouse_leave();
}

void Application::UI::Parent::handle_mouse_move(float mX, float mY)
{
	const auto length = this->elements.size() - 1;
	bool e_handled = false;

	for (int i = length; i >= 0; i--)
	{
		auto* element = (UI::InteractiveElement*)this->elements[i];
		
		if (
			e_handled == false &&
			element->hidden == false &&
			element->point_belongs({(LONG)(mX),(LONG)(mY)})
			)
		{
			if (element->hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(mX,mY);
			e_handled = true;
		}
		else if (element->hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	InteractiveElement::handle_mouse_move(mX, mY);
}

void Application::UI::Parent::handle_mouse_scroll(int delta)
{
	for (auto* element : this->elements)
	{
		if (element->hovered)
			element->handle_mouse_scroll(delta);
	}
	InteractiveElement::handle_mouse_scroll(delta);
}

void Application::UI::Parent::set_index_offset(UINT offset)
{
	this->index_offset = offset;
}

void Application::UI::Parent::draw(Render::DrawEvent* event)
{
	for (auto* element : this->elements)
		if(element->hidden == false)
			element->draw(event);
}

void Application::UI::Parent::set_pos(float x, float y)
{
	this->move_by(x - this->position.x, y - this->position.y);
}

void Application::UI::Parent::set_color(float r, float g, float b)
{
	for (auto* element : this->elements)
		element->set_color(r, g, b);
}

bool Application::UI::Parent::point_belongs(POINT point)
{
	for (auto* element : this->elements)
		if (element->point_belongs(point))
			return true;
	return false;
}

UINT Application::UI::Parent::size()
{
	UINT size = 0;
	for (auto* element : this->elements)
		size += element->size();

	return size;
}

void Application::UI::Parent::move_by(float x, float y)
{
	for (auto* element : this->elements)
		element->move_by(x,y);
}

void Application::UI::Parent::init(Application::InteractiveForm* pForm)
{	
	UINT index = this->index_offset+this->__index;
	
	for(auto*element:this->elements)
	{
		element->set_index(index);

		element->init(this->pForm);
		element->set__parent(this);

		element->move_by(this->position.x, this->position.y);
		
		index += element->size();
	}
}

void Application::UI::Parent::foreach(std::function<void(InteractiveElement* element)> iterator)
{
	for (auto* element : elements)
	{
		iterator(element);
	}
}

Application::UI::InteractiveElement* Application::UI::Parent::element_at(UINT index)
{
	return this->elements[index];
}

Application::UI::Parent* Application::UI::Parent::add_element(InteractiveElement* element)
{
	this->elements.push_back(element);
	return this;
}

Application::UI::Parent* Application::UI::Parent::add_element(InteractiveElement* element, bool visible)
{
	element->hidden = !visible;
	return this->add_element(element);
}

