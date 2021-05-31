#include "ItemList.h"

void Application::UI::ItemList::on_initialize()
{
	Panel::on_initialize();

	auto this_resolution = this->get_resolution();

	float offset = 0;
	Panel::foreach([&](InteractiveElement* element)
		{
			auto element_resolution = element->get_resolution();
			auto margin = element->styles.margin;
			element->set_resolution(
				this_resolution.width - margin.x - margin.z,
				element_resolution.height
			);
			element->move_by(margin.x, offset - margin.y);
			//element->set_pos(margin.x, offset - margin.y);

			offset -= (element_resolution.height + margin.y + margin.w);
		});
}

Application::UI::ItemList::ItemList(Render::Position position, Render::Resolution resolution, Render::Color color)
	: Panel(position,resolution,color)
{
	Panel::styles.overflow = VISIBLE_STATE_HIDDEN;
}

Application::UI::ElementDescription Application::UI::ItemList::get_desc()
{
	return { true,"ItemList" };
}

void Application::UI::ItemList::handle_mouse_scroll(int delta)
{
	Panel::handle_mouse_scroll(delta);

	Panel::foreach([delta](InteractiveElement* element)
		{
			element->move_by(0, (float)delta*-1);
		});
}
