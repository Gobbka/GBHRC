#pragma once
#include <Windows.h>
#include "../../Render/Scene/Scene.h"

namespace Application {

	namespace Render
	{
		class Engine;
	}
	
	namespace Canvas {
		class CanvasElement;

		class CanvasForm : public Application::Render::Scene
		{
		public:
			void draw_element(Render::IRenderObject* obj, Render::DrawEvent* event) override;
			
			void update_markup(Application::Render::Engine* pEngine);
			void add_element(CanvasElement* element);
		};
	}
}
