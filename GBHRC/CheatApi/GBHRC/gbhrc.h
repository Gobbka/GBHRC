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
		class Scene;
	}
}

namespace GBHRC
{
	class Context
	{
	private:
		Config* config;
		UnityEngine::Transform* aim_target = nullptr;
		
		Context();

		void draw_esp(Application::Render::Scene* pScene);
		
	public:
		static Context* instance();

		static void static_draw_callback(Application::Render::Scene* pScene);
	};

}

