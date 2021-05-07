#pragma once
#include <vector>

#include "InteractiveElement.h"
#include "../../../../Render/Scene/IRenderObject.h"

namespace Application
{
	namespace UI
	{
		
		class Parent : public InteractiveElement
		{
		private:
			std::vector<InteractiveElement*> elements;
			UINT index_offset=0;
		protected:
			void set_index_offset(UINT offset);
		public:
			void __draw(Render::Engine*pEngine) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			bool point_belongs(POINT point) override;
			UINT size() override;
			void move_by(float x, float y) override;
			
			void init(Application::InteractiveForm* pForm) override;
			
			Parent* add_element(InteractiveElement* element);
		};
	}
}
