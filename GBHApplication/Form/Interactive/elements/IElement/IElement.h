#pragma once
#include "../../../../Application.h"


namespace Application
{
	namespace UI {
		
		class IElement : public Render::IRenderObject
		{
		public:
			virtual ~IElement() = default;
			typedef void(*EventCallback)(UIElementEventArgs args);
		protected:
			Application::InteractiveForm* pForm = nullptr;
			Render::Position position{ 0,0 };
			static void default_event_callback(UIElementEventArgs args) {};
		public:
			bool hovered = false;

			Render::Position get_position() const;

			EventCallback onMouseEnter = default_event_callback;
			EventCallback onMouseLeave = default_event_callback;
			typedef void(*tMouseMoveCallbackEvent)(UIElementEventArgs args,float mX,float mY);
			tMouseMoveCallbackEvent onMouseMove = [](UIElementEventArgs,float,float){};
			EventCallback onMouseUp = default_event_callback;
			EventCallback onMouseDown = default_event_callback;

			void move_by(float x, float y) override;

			virtual void init(Application::InteractiveForm* pForm) = 0;

			GVertex::Vertex* get_ptr() const;
		};
	}
}