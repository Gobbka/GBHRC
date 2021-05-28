#include "EngineEvents.h"
#include "../Engine/Engine.h"
#include "../Scene/CanvasScene.h"

void Application::Render::DrawEvent::draw_element(Canvas::CanvasElement* object)
{
	this->element_ptr = object->get_index();
	object->draw(this);
}

void Application::Render::DrawEvent::draw(UINT count, UINT offset)
{
	this->engine->pDevContext->Draw(count, this->element_ptr + offset);
}

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

Application::Render::DrawEvent::DrawEvent(Engine* engine, CanvasScene* scene, ID3D11RasterizerState* old_state)
{
	this->engine = engine;
	this->scene = scene;
	this->old_state = old_state;
	
	this->scenes_completed = 0;
}
