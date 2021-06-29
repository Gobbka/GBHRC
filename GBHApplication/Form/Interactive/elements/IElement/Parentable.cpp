#include "Parentable.h"

#include "../../../../Render/Scene/CanvasScene.h"


void Application::UI::ChildrenCollection::foreach(std::function<void(Application::UI::InteractiveElement* element)> iterator)
{
	for(auto*element:this->_children)
		iterator(element);
	
}

void Application::UI::ChildrenCollection::append(UI::InteractiveElement* child)
{
	this->_children.push_back(child);
}

size_t Application::UI::ChildrenCollection::count()
{
	return this->_children.size();
}

Application::UI::InteractiveElement* Application::UI::ChildrenCollection::operator[](UINT index)
{
	return this->_children[index];
}


void Application::UI::Parent::handle_mouse_up()
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_up();
	});
	
	InteractiveElement::handle_mouse_up();
}

void Application::UI::Parent::handle_mouse_down()
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_down();
	});
	
	InteractiveElement::handle_mouse_down();
}

void Application::UI::Parent::handle_mouse_enter()
{
	InteractiveElement::handle_mouse_enter();
}

void Application::UI::Parent::handle_mouse_leave()
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		element->handle_mouse_leave();
	});
	
	InteractiveElement::handle_mouse_leave();
}

void Application::UI::Parent::handle_mouse_move(float mX, float mY)
{
	const auto length = this->_children.count() - 1;
	bool e_handled = false;

	for (long long i = length; i >= 0; i--)
	{
		auto* element = (UI::InteractiveElement*)this->_children[i];
		
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
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_scroll(delta);
	});
	
	InteractiveElement::handle_mouse_scroll(delta);
}

void Application::UI::Parent::on_initialize()
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		element->initialize(this->form);
		element->move_by(this->offset_position.x, this->offset_position.y);
	});

	this->initialized = true;
}

Application::UI::ChildrenCollection* Application::UI::Parent::children()
{
	return &this->_children;
}

Application::UI::Parent::Parent(Render::Position position)
{
	this->offset_position = position;
}

void Application::UI::Parent::draw(Render::DrawEvent* event)
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.visible == VisibleState::VISIBLE_STATE_VISIBLE)
			element->draw(event);
	});
}

void Application::UI::Parent::set_color(Render::Color4 color)
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		element->set_color(color);
	});
}

void Application::UI::Parent::move_by(float x, float y)
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		element->move_by(x, y);
	});
}

//void Application::UI::Parent::init()
//{
//	for (auto* element : this->elements)
//	{
//		element->initialize(this->pForm);
//	}
//}


Application::UI::InteractiveElement* Application::UI::Parent::element_at(UINT index)
{
	return this->_children[index];
}

Application::UI::Parent* Application::UI::Parent::add_element(InteractiveElement* element)
{
	if (element->have_parent())
		return this;
	
	element->set_parent(this);
	this->_children.append(element);
	
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
	return this->add_element(element);
}

