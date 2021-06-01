#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include "../../Render/Text/Text.h"
#include "../../Application.h"
#include <windowsx.h>

void Application::InteractiveForm::render_components(Render::DrawEvent* event)
{
	for(auto*element:this->interactive_elements)
	{
		if (element->state.visible == UI::VISIBLE_STATE_VISIBLE)
			element->draw(event);
		
		event->mask_clear();
	}
}

void Application::InteractiveForm::foreach(std::function<void(UI::InteractiveElement* element)> callback)
{
	for(auto*element:this->interactive_elements)
		callback(element);
}

void Application::InteractiveForm::drag_move(UI::InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = ( Application::Context::get_client_cursor_point()); // Application::point_to_center
	DEBUG_LOG(std::dec<< cursor.x << " " << cursor.x << " " << pos.x << " "<<pos.y);
	//this->dragged = new DragStruct{ cursor.x - (LONG)pos.x ,cursor.y - (LONG)pos.y ,element};
}

void Application::InteractiveForm::free_drag_move()
{
	if (this->dragged == nullptr) return;

	delete this->dragged;
	this->dragged = nullptr;
}

void Application::InteractiveForm::initialize_components(Render::Engine* pEngine)
{
	
	for (auto* element : this->interactive_elements)
		element->add_elements(this);

	CanvasScene::initialize_components(pEngine);

	for (auto* element : this->interactive_elements)
		element->initialize(this);
	
}

Application::InteractiveForm* Application::InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->interactive_elements.push_back(element);
	return this;
}

void Application::InteractiveForm::on_mouse_move(int mx,int my)
{
	if (this->hidden == true)
		return;

	auto screen_resolution = Application::Context::get_window_resolution();
	const Render::Position center{ (screen_resolution.width / 2),(screen_resolution.height / 2) };

	const Render::Position cursor{ mx - center.x , center.y - my };

	if (this->dragged)
	{
		this->dragged->element->set_pos(cursor.x - this->dragged->dragged_offset.x, cursor.y + this->dragged->dragged_offset.y);
		return;
	}

	const auto length = this->interactive_elements.size();
	bool e_handled = false;

	for (auto i = length; i > 0; i--)
	{
		auto* element = this->interactive_elements[i-1];
		
		if (
			element->state.visible == UI::VISIBLE_STATE_VISIBLE &&
			e_handled == false &&
			element->point_belongs(cursor)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(cursor.x, cursor.y);
			e_handled = true;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	return;
}

void Application::InteractiveForm::on_mouse_scroll(short direction)
{
	this->foreach([direction](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);
		});
	return;
}

void Application::InteractiveForm::on_lbmouse_up()
{
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_up();
		});

	this->free_drag_move();

	return;
}

void Application::InteractiveForm::on_lbmouse_down()
{
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_down();
		});
	return;
}

