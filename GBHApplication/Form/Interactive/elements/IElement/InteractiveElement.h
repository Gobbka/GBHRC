#pragma once
#include "../../../../Render/Render.h"
#include "../../../../Render/Scene/IRenderObject.h"
#include "../../../../Application.h"
#include "functional"
#include "../../../../configuration/drawconf.h"

namespace Application {
	class InteractiveForm;
}

namespace Application
{
	namespace UI {

		class Parent;
		class InteractiveElement;
		typedef InteractiveElement* UIElementEventArgs;

		enum VisibleState : bool
		{
			VISIBLE_STATE_VISIBLE = true,
			VISIBLE_STATE_HIDDEN  = false,
		};

		struct ElementStyles
		{
			VisibleState      overflow = VISIBLE_STATE_VISIBLE;
			#define MARGIN_AUTO -1
			DirectX::XMFLOAT4 margin   = { 0,0,0,0};
		};

		struct ElementState
		{
			bool         hovered = false;
			VisibleState visible = VISIBLE_STATE_VISIBLE;
		};

		struct ElementDescription
		{
			// flags

			bool has_children : 1;

			// other

			const char* string_name;

			ElementDescription(bool has_children, const char* string_name);
		};


		class InteractiveElement : public Render::IRenderObject
		{
		public:
			typedef std::function<void(UIElementEventArgs)> EventCallback;
		protected:
			// protected variables

			InteractiveForm* pForm = nullptr;
			Parent*          _parent = nullptr;
		protected:
			static void default_event_callback (UIElementEventArgs args) {}
			virtual void on_initialize(){};
		public:
			// public variables
			UINT unique_id = 0;

			ElementStyles styles;
			ElementState  state;
			
			// for debug purposes
			// or what u wanna
		public:
			// public getters

			// return's screen position
			virtual Render::Position get_position() PURE;

			virtual ElementDescription get_desc() PURE;

			virtual Render::Resolution get_resolution() PURE;

			virtual bool point_belongs(Render::Position point) PURE;
			
			// return's parent, if have
			Parent* get_parent() const;
			// return's form where this object where registered
			InteractiveForm* get_form() const;
		public:
			// public setters

			FIELD_SETTER(Parent*, _parent);

			virtual InteractiveElement* set_resolution(float width,float height) PURE;

			void set_margin(float x,float y);
			void set_margin(float x,float y,float z,float w);
			
		public:
			// public voids
			void draw(Render::DrawEvent* event) override PURE;

			void initialize(InteractiveForm*form);
			virtual void add_elements(Render::CanvasScene*scene) {};
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

		struct InteractiveElementDesc {
			InteractiveElement* (*create_func)(InteractiveElementDesc*);
			Render::Position pos{0,0};
			Render::Resolution resolution{0,0};
			Render::Color color{0,0,0,0};

			InteractiveElement* new_instance();
		};
	}
}
