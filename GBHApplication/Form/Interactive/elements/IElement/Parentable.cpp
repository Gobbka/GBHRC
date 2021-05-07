#include "Parentable.h"

#include "../../../../Render/Scene/Scene.h"

void Application::UI::Parent::set_index_offset(UINT offset)
{
	this->index_offset = offset;
}

void Application::UI::Parent::__draw(Render::Engine*engine)
{
	for (auto* element : this->elements)
		element->__draw(engine);
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
	return 0;
}

void Application::UI::Parent::move_by(float x, float y)
{
	for (auto* element : this->elements)
		element->move_by(x,y);
}

void Application::UI::Parent::init(Application::InteractiveForm* pForm)
{
	DEBUG_LOG("INITING");
	
	UINT size = this->index_offset;
	
	for(auto*element:this->elements)
	{
		DEBUG_LOG("ELEMENT:" << element << " "<<this->pForm);
		element->init(this->pForm);
		element->set_parent(this);

		element->set_index(size);
		element->move_by(this->position.x, this->position.y);
		
		size += element->size();
	}
}

void Application::UI::Parent::add_element(InteractiveElement* element)
{
	this->elements.push_back(element);
}
