#pragma once
#include "../Panel/Panel.h"

namespace Application
{
	namespace UI
	{
		class ItemList : public Panel
		{
		public:
			ItemList(Render::Position position, Render::Resolution resolution, Render::Color color);
		public:
			ElementDescription get_desc() override;
			
			void init() override;
		};
	}
}
