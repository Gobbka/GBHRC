#pragma once
#include "../Application.h"

namespace Application {
	class CanvasForm : public Application::Render::Scene
	{
	public:
		void update_markup(Application::Render::Engine* pEngine);
	};
}
