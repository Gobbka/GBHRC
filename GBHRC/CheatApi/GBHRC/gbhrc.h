#pragma once
#include "config/Config.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"

namespace Application {
	namespace Canvas {
		class CanvasForm;
	}
}

namespace Application {
	namespace Render {
		class Engine;
		class Scene;
	}
}

namespace GBHRC
{

	struct EspBox
	{
		Application::Canvas::Rectangle* box;
		Application::Canvas::Rectangle* max_health_box;
		Application::Canvas::Rectangle* health_box;
	};
	
	class Context
	{
	private:
		HMODULE DllInst;
		UnityEngine::Transform* aim_target = nullptr;
		
		Context();

		void draw_esp(Application::Render::Scene* pScene,Application::Render::Engine*engine);

		std::vector<EspBox*> esp_boxes;
		Application::Canvas::CanvasForm* esp_scene;
	public:
		void set_esp(bool status);
		
		Config* config;

		
		bool aim_active = false;

		void implement(HMODULE DllInst);
		static Context* instance();

		void make_esp_boxes();
		void set_esp_scene(Application::Canvas::CanvasForm*form);

		static void static_draw_callback(Application::Render::DrawEvent*event);
		void life_cycle();
	};

}

