#pragma once
#include "../../../../Render/Render.h"
#include "../../../../Render/Scene/IRenderObject.h"
#include "../../../../Application.h"


namespace Application {
	class InteractiveForm;
}

namespace Application
{
	namespace UI {

		class Parent;
		class InteractiveElement;
		typedef InteractiveElement* UIElementEventArgs;
		
		class InteractiveElement : public Render::IRenderObject
		{
		public:
			virtual ~InteractiveElement() = default;
			typedef void(__thiscall*EventCallback)(UIElementEventArgs args);
		protected:
			// protected variables

			InteractiveForm* pForm = nullptr;
			Render::Position position{ 0,0 };
			Parent* _parent = nullptr;
		protected:
			static void default_event_callback(UIElementEventArgs args) {};
		public:
			// public variables
			
			bool hovered = false;

		public:
			// public getters

			Render::Position get_position() const;

			GVertex::Vertex* get_ptr() const;
			Parent* get_parent() const;
			InteractiveForm* get_form() const;
			UINT size() override = 0;

			bool point_belongs(POINT point) override = 0;
		public:
			// public setters

			FIELD_SETTER(Parent*, _parent);
			FIELD_SETTER(InteractiveForm*, pForm);

			void set_pos(float x, float y) override = 0;
			void set_color(float r, float g, float b) override = 0;
			
		public:
			// public voids

			void move_by(float x, float y) override = 0;
			virtual void init(Application::InteractiveForm* pForm) = 0;
			void __draw(Render::Engine* engine) override = 0;
			
		public:
			// public callbacks
			
			EventCallback onMouseEnter = default_event_callback;
			EventCallback onMouseLeave = default_event_callback;
			void(*onMouseMove)(UIElementEventArgs args, float mX, float mY) = [](UIElementEventArgs,float,float){};
			EventCallback onMouseUp = default_event_callback;
			EventCallback onMouseDown = default_event_callback;

		public:
			//====================
			// EVENT HANDLER'S
			// if you wanna override something in your class,
			// u must to call base func if think that event need to be handled
			//

			virtual void handle_mouse_move(float mX, float mY);
			virtual void handle_mouse_leave();
			virtual void handle_mouse_enter();
			virtual void handle_mouse_up();
			virtual void handle_mouse_down();
		};
	}
}
