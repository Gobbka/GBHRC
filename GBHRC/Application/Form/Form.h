#pragma once
#include "../Application.h"

namespace Application
{
	class Form : public Render::Scene
	{
	public:
		void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
