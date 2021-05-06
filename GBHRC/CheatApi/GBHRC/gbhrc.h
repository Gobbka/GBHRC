#pragma once
#include "config/Config.h"
#include "../BrokeProtocol/BrokeProtocol.h"

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
	class Context
	{
	private:
		HMODULE DllInst;
		Config* config;
		UnityEngine::Transform* aim_target = nullptr;
		
		Context();

		void draw_esp(Application::Render::Scene* pScene,Application::Render::Engine*engine);
		
	public:
		bool aim_active = false;

		void implement(HMODULE DllInst);
		static Context* instance();

		static void static_draw_callback(Application::Render::Scene* pScene,Application::Render::Engine*engine);
		void life_cycle();
	};

}

