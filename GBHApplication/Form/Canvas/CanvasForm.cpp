#include "CanvasForm.h"

#include "elements/IElement/CanvasElement.h"
#include "../../Render/Engine/Engine.h"

void Application::Canvas::CanvasForm::draw_element(Render::IRenderObject* obj, Render::DrawEvent* event)
{
	// event->engine->pDevContext->PSSetShader(nullptr, nullptr, 0);

	static auto*nigger = event->engine->make_vertex_buffer(5);
	nigger->data[0] = GVertex::Vertex(-50.f,50.f, 1.f,1,1,1,1);
	nigger->data[1] = GVertex::Vertex(-50,-50, 1.f, 1, 1, 1, 1);
	nigger->data[2] = GVertex::Vertex(500,-50, 1.f, 1, 1, 1, 1);
	nigger->data[3] = GVertex::Vertex(500,50, 1.f,1,1,1,1);
	nigger->data[4] = GVertex::Vertex(-50,50,1.f,1,1,1,1);


	event->engine->set_vbuffer(nigger);


	auto* pContext = event->engine->pDevContext;
	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(nigger->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	memcpy(subdata.pData, nigger->data, nigger->size * sizeof(GVertex::Vertex));
	pContext->Unmap(nigger->buffer, 0);

	event->engine->pDevContext->Draw(5, 0);

	event->engine->set_vbuffer(this->get_vbuffer());
	
	if (((Canvas::CanvasElement*)obj)->render == true)
	{
		
		//event->engine->get_mask()->set_discard_mask();
		//
		//obj->draw(event);
		event->engine->get_mask()->unset_mask();
		obj->draw(event);

	}
}

void Application::Canvas::CanvasForm::update_markup(Application::Render::Engine* pEngine)
{

	this->alloc_vbuffer(pEngine);
	UINT size = 0;
	
	Scene::foreach([&size,this](Render::IRenderObject* obj)
		{
			((Canvas::CanvasElement*)obj)->set_index(size);
			((Canvas::CanvasElement*)obj)->init(this);
			size += obj->size();
		});
}

Application::Canvas::CanvasForm* Application::Canvas::CanvasForm::add_element(CanvasElement* element)
{
	this->add_render_object(element);
	return this;
}
