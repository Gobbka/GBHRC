#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include "../../Render/Text/Text.h"
#include "../../Application.h"
#include <windowsx.h>

void Application::InteractiveForm::render_components(Render::DrawEvent* event)
{
	for(auto*element:this->childs)
	{
		if (element->state.visible == UI::VISIBLE_STATE_VISIBLE)
			element->draw(event);
		
		event->mask_clear();
	}
}

void Application::InteractiveForm::foreach(std::function<void(UI::InteractiveElement* element)> callback)
{
	for(auto*element:this->childs)
		callback(element);
}

void Application::InteractiveForm::drag_move(UI::InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = Application::Context::point_to_center( Application::Context::get_client_cursor_point()); // Application::point_to_center
	this->dragged = new DragStruct{ cursor.x - pos.x ,cursor.y - pos.y ,element};
}

void Application::InteractiveForm::free_drag_move()
{
	if (this->dragged == nullptr) return;

	delete this->dragged;
	this->dragged = nullptr;
}

//void Application::InteractiveForm::initialize_components(Render::Engine* pEngine)
//{
//	
//	for (auto* element : this->interactive_elements)
//		element->add_elements(this);
//
//	CanvasScene::initialize_components(pEngine);
//
//	for (auto* element : this->interactive_elements)
//		element->initialize(this);
//	
//}

bool Application::InteractiveForm::has_element(UI::InteractiveElement* element)
{
	for (auto* in_element : this->childs)
		if (element == in_element)
			return true;
	return false;
}


Application::InteractiveForm* Application::InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->childs.push_back(element);
	element->initialize(this);
	return this;
}

Application::InteractiveForm::InteractiveForm(Render::Engine* pEngine)
	: CanvasScene(pEngine)
{
}

Application::InteractiveForm::~InteractiveForm()
{
	
}

Application::Interaction::EventStatus Application::InteractiveForm::on_mouse_move(int mx,int my)
{
	if (this->hidden())
		return Interaction::EventStatus::none;

	const Render::Position cursor = Application::Context::point_to_center(Render::Position{ (float)mx,(float)my });

	if (this->dragged)
	{
		this->dragged->element->set_pos(cursor.x - this->dragged->dragged_offset.x, cursor.y - this->dragged->dragged_offset.y);
		return Interaction::EventStatus::handled;
	}

	auto e_handled = Interaction::EventStatus::none;

	for (auto i = this->childs.size(); i --> 0;)
	{
		auto* element = this->childs[i];
		
		if (
			element->state.visible == UI::VISIBLE_STATE_VISIBLE &&
			e_handled == Interaction::EventStatus::none &&
			element->point_belongs(cursor)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(cursor.x, cursor.y);
			e_handled = Interaction::EventStatus::handled;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	return e_handled;
}

Application::Interaction::EventStatus Application::InteractiveForm::on_mouse_scroll(short direction)
{
	if (this->hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([direction](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);
		});
	return Interaction::EventStatus::none;
}

Application::Interaction::EventStatus Application::InteractiveForm::on_lbmouse_up()
{
	if (this->hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_up();
		});

	this->free_drag_move();

	return Interaction::EventStatus::none;
}

Application::Interaction::EventStatus Application::InteractiveForm::on_lbmouse_down()
{
	if (this->hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_down();
		});
	return Interaction::EventStatus::none;
}

