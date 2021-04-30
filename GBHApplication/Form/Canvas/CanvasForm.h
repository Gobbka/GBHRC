#pragma once
#include "../../Application.h"

namespace Application {
	
	namespace Canvas {
		class IElement;

		class CanvasForm : public Application::Render::Scene
		{
		public:
			void update_markup(Application::Render::Engine* pEngine);
			void add_elements(UINT count,Canvas::IElement* element...);
		};
	}
}

#include "elements/IElement/IElement.h"
