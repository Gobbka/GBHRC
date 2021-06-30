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

		class ReadChildrenCollection {
		protected:
			std::vector<UI::InteractiveElement*> _children;

		public:
			void foreach(std::function<void(InteractiveElement* element)> iterator);
			
			size_t count();

			UI::InteractiveElement* operator[](UINT index);
		};

		class ReadWriteChildrenCollection : public ReadChildrenCollection {
		public:
			void append(UI::InteractiveElement* child);
		};
		
		class Parent : public InteractiveElement
		{
		private:
			Render::Position _offset_position;
			ReadWriteChildrenCollection _children;
			bool initialized = false;
		protected:
			void handle_mouse_up() override;
			void handle_mouse_down() override;
			void handle_mouse_enter() override;
			void handle_mouse_leave() override;
			void handle_mouse_move(float mX, float mY) override;
			void handle_mouse_scroll(int delta) override;

			void on_initialize() override;
		public:
			ReadChildrenCollection* children();
			
			Parent(Render::Position position);
			
			void draw(Render::DrawEvent*event) override;
			void set_color(Render::Color4 color) override;
			void move_by(float x, float y) override;

			InteractiveElement* element_at(UINT index);
			
			virtual Parent* add_element(InteractiveElement* element);
			Parent* add_element(InteractiveElement* element,bool visible);
		};
	}
}
