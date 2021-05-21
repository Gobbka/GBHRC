#pragma once
#include <vector>

#include "InteractiveElement.h"
#include "../../../../Render/Scene/IRenderObject.h"

namespace Application {
	namespace Render {
		class Text;
	}
}

namespace Application
{
	namespace UI
	{
		
		class Parent : public InteractiveElement
		{
		private:
			std::vector<InteractiveElement*> elements;
			UINT index_offset=0;

			void handle_mouse_up() override;
			void handle_mouse_down() override;
			void handle_mouse_enter() override;
			void handle_mouse_leave() override;
			void handle_mouse_move(float mX, float mY) override;
			void handle_mouse_scroll(int delta) override;
		protected:
			void set_index_offset(UINT offset);
		public:
			
			void draw(Render::DrawEvent*event) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			bool point_belongs(POINT point) override;
			UINT size() override;
			void move_by(float x, float y) override;
			
			void init() override;

			void foreach(std::function<void(InteractiveElement* element)> iterator);
			InteractiveElement* element_at(UINT index);
			
			Parent* add_element(InteractiveElement* element);
			Parent* add_element(InteractiveElement* element,bool visible);
		};
	}
}
