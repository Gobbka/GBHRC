#include "EngineEvents.h"
#include "../Engine/Engine.h"
#include "../Scene/CanvasScene.h"
#include "../Engine/BlendEngine.h"
#include "../d3d/Buffers/VertexBuffer.h"

void Application::Render::D3D11DrawEvent::set_alpha(float alpha)
{
	this->engine->get_blend_engine()->set_alpha(engine->get_constant_buffer(),alpha);
}

void Application::Render::D3D11DrawEvent::draw_element(Canvas::CanvasElement* object)
{
	this->element_index = object->get_index();
	object->draw(this);
}

void Application::Render::D3D11DrawEvent::draw_vertex(UINT count, UINT offset) const
{
	this->engine->pDevContext->Draw(count, this->element_index + offset);
}

void Application::Render::D3D11DrawEvent::mask_draw_begin() const
{
	this->engine->get_mask()->set_draw_mask(mask_layer_depth);
}

void Application::Render::D3D11DrawEvent::mask_discard_begin(bool increase)
{
	if(increase)
		this->mask_layer_depth++;
	this->engine->get_mask()->set_discard_mask(mask_layer_depth);
}

void Application::Render::D3D11DrawEvent::mask_discard_end(bool decrease)
{
	if(decrease)
		this->mask_layer_depth--;
	this->engine->get_mask()->unset_mask();
}

void Application::Render::D3D11DrawEvent::mask_set_depth(BYTE new_index)
{
	this->mask_layer_depth = new_index;
}

BYTE Application::Render::D3D11DrawEvent::mask_get_depth()
{
	return this->mask_layer_depth;
}

void Application::Render::D3D11DrawEvent::mask_clear()
{
	this->engine->get_mask()->clearBuffer();
}

void Application::Render::D3D11DrawEvent::mask_reset()
{
	this->engine->get_mask()->reset_mask(this->mask_layer_depth);
}

ID3D11DeviceContext* Application::Render::D3D11DrawEvent::get_context() const
{
	return this->engine->pDevContext;
}

void Application::Render::D3D11DrawEvent::reset_render_state()
{
	// TODO: know what needed to reset to draw fine
	this->engine->render_prepare();
	engine->pDevContext->RSSetState((ID3D11RasterizerState*)this->old_state);
	this->scene->get_vbuffer()->bind();
	//this->engine->set_vbuffer(this->scene->get_vbuffer());
}

Application::Render::D3D11DrawEvent::D3D11DrawEvent(Engine* engine, CanvasScene* scene, ID3D11RasterizerState* old_state)
{
	this->engine = engine;
	this->scene = scene;
	this->old_state = old_state;
	
	this->scenes_completed = 0;
	this->element_index = 0;
	this->mask_layer_depth = 0;
}
