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
