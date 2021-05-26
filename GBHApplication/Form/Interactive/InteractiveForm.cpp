#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include "../../Render/Text/Text.h"
#include "../../Application.h"
#include <windowsx.h>

void Application::InteractiveForm::draw_element(Render::IRenderObject* obj, Render::DrawEvent* event)
{
	if (((UI::InteractiveElement*)obj)->state.visible == UI::VISIBLE_STATE_VISIBLE)
		event->draw_element(obj);
}

void Application::InteractiveForm::drag_move(UI::InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = ( Application::get_client_cursor_point()); // Application::point_to_center
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
	this->alloc_vbuffer(pEngine);
	UINT size = 0;

	Scene::foreach([this, &size](Render::IRenderObject* obj)
		{
			auto* iUIObject = (UI::InteractiveElement*)obj;
			iUIObject->initialize(this,size);

			size += obj->size();
		});
}

Application::InteractiveForm* Application::InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->add_render_object(element);
	return this;
}

void Application::InteractiveForm::on_lbmouse_down()
{
	this->foreach([](Render::IRenderObject* obj)
		{
			auto* element = (UI::InteractiveElement*)obj;
			if (element->state.hovered == true)
				element->handle_mouse_down();
		});
	return;
}

void Application::InteractiveForm::on_mouse_move(int mx,int my)
{
	if (this->hidden == true)
		return;

	auto screen_resolution = Application::get_window_resolution();
	const Render::Position center{ (screen_resolution.width / 2),(screen_resolution.height / 2) };

	const Render::Position cursor{ mx - center.x , center.y - my };

	if (this->dragged)
	{
		this->dragged->element->set_pos(cursor.x - this->dragged->dragged_offset.x, cursor.y + this->dragged->dragged_offset.y);
		return;
	}

	const auto length = this->elements_length();
	bool e_handled = false;

	for (auto i = length; i > 0; i--)
	{
		auto* element = (UI::InteractiveElement*)this->element_at(i-1);
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
	this->foreach([direction](Render::IRenderObject* obj)
		{
			auto* element = (UI::InteractiveElement*)obj;
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);

		});
	return;
}

void Application::InteractiveForm::on_lbmouse_up()
{
	this->foreach([](Render::IRenderObject* obj)
		{
			auto* element = (UI::InteractiveElement*)obj;
			if (element->state.hovered == true)
				element->handle_mouse_up();
		});

	this->free_drag_move();

	return;
}

