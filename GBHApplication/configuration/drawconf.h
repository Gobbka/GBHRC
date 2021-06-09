#pragma once
#include "projectconf.h"

#ifdef DRAW_METHOD_DIRECT_X_11
namespace Application {
	namespace Render {
		struct D3D11DrawEvent;

		typedef Application::Render::D3D11DrawEvent DrawEvent;
	}
}
#endif
