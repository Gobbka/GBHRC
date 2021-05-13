#include "EngineEvents.h"
#include "../Engine/Engine.h"

ID3D11DeviceContext* Application::Render::DrawEvent::get_context() const
{
	return this->engine->pDevContext;
}
