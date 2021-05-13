#include "EngineEvents.h"
#include "../Engine/Engine.h"
#include "../Scene/Scene.h"

ID3D11DeviceContext* Application::Render::DrawEvent::get_context() const
{
	return this->engine->pDevContext;
}

void Application::Render::DrawEvent::reset_render_state()
{
	// TODO: know what needed to reset to draw fine
	this->engine->render_prepare();
	engine->pDevContext->RSSetState((ID3D11RasterizerState*)this->old_state);
	this->engine->set_vbuffer(this->scene->get_vbuffer());
}
