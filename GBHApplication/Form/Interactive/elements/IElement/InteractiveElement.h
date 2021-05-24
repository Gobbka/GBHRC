#pragma once
#include "../../../../Render/Render.h"
#include "../../../../Render/Scene/IRenderObject.h"
#include "../../../../Application.h"
#include "functional"

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
			typedef std::function<void(UIElementEventArgs)> EventCallback;
		protected:
			// protected variables

			InteractiveForm* pForm = nullptr;
			Render::Position position{ 0,0 };
			Parent* _parent = nullptr;
		protected:
			virtual void init(){}
			void draw(Render::DrawEvent* event) override PURE;
			static void default_event_callback (UIElementEventArgs args) {}
		public:
			// public variables

			// if value is a true, this object will handle all interactive events (such as click,mousescroll e.t.d)
			bool hovered = false;
			// if value is a true, this object will not render
			bool hidden = false;

			// for debug purposes
			// or what u wanna
			UINT unique_id = 0;
		public:
			// public getters

			// return's screen position
			Render::Position get_position() const;
			// return's memory region pointer where you can edit vertex
			GVertex::Vertex* get_ptr();
			// vertex size of object
			UINT size() override = 0; 
			// return's parent, if have
			Parent* get_parent() const;
			// return's form where this object where registered
			InteractiveForm* get_form() const;

			
			bool point_belongs(Render::Position point) override PURE;
		public:
			// public setters

			FIELD_SETTER(Parent*, _parent);

			void set_pos(float x, float y) override = 0;
			void set_color(float r, float g, float b) override = 0;
			
		public:
			// public voids

			void move_by(float x, float y) override = 0;
			void initialize(Application::InteractiveForm* pForm,UINT index);
		protected:
			
		public:
			// public callbacks
			
			EventCallback onMouseEnter = default_event_callback;
			EventCallback onMouseLeave = default_event_callback;
			void(*onMouseMove)(UIElementEventArgs args, float mX, float mY) = [](UIElementEventArgs,float,float){};
			std::function<void(UIElementEventArgs args, int delta)>onMouseScroll = [](UIElementEventArgs,int){};
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
			virtual void handle_mouse_scroll(int delta);
		};
	}
}
