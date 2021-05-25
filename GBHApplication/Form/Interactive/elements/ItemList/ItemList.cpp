#include "ItemList.h"

Application::UI::ItemList::ItemList(Render::Position position, Render::Resolution resolution, Render::Color color)
	: Panel(position,resolution,color)
{
	
}

Application::UI::ElementDescription Application::UI::ItemList::get_desc()
{
	return { true,"ItemList" };
}

void Application::UI::ItemList::init()
{
	Panel::init();

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
			element->set_pos(margin.x, offset - margin.y);

			offset -= (element_resolution.height + margin.y + margin.w);
		});
}
