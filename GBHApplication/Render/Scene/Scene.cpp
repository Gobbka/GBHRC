#include "Scene.h"
#include "../../Render/Engine/Engine.h"
#include "../../Application.h"

#define DRAW_ASSERT if(this->hidden==true) return

void Application::Render::Scene::alloc_vbuffer(Render::Engine* pEngine)
{
	delete this->pVBuffer;
	const UINT size = this->total_size();

	this->pVBuffer = pEngine->make_vertex_buffer(size);
}

void Application::Render::Scene::update(ID3D11DeviceContext* pContext)
{
	DRAW_ASSERT;

	if (this->render_callback != nullptr)
		render_callback(this);

	if (this->pVBuffer->size <= 0)
		return;
	
	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(this->pVBuffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	memcpy(subdata.pData, this->pVBuffer->data, this->pVBuffer->size * sizeof(GVertex::Vertex));
	pContext->Unmap(this->pVBuffer->buffer, 0);
}

void Application::Render::Scene::render(ID3D11DeviceContext* pContext, ID3D11Device* pDevice)
{
	DRAW_ASSERT;
	
	UINT stride = sizeof(GVertex::Vertex);
	UINT offset = 0;

	pContext->IASetVertexBuffers(0, 1, &this->pVBuffer->buffer, &stride, &offset);

	for (auto* element : this->pElements)
	{
		element->__draw(pContext,pDevice);
	}

}

void Application::Render::Scene::foreach(std::function<void(IRenderObject*)> const& nigger)
{
	for (auto* element : this->pElements)
		nigger(element);
}

UINT Application::Render::Scene::total_size()
{
	UINT size = 0;
	for (auto* element : this->pElements)
		size += element->size();
	return size;
}

void Application::Render::Scene::add_render_object(IRenderObject* object)
{
	this->pElements.push_back(object);
}

Application::Render::IRenderObject* Application::Render::Scene::element_at(UINT index)
{
	return this->pElements[index];
}

void Application::Render::Scene::set_resolution(Resolution resolution)
{
	this->resolution = resolution;
}


GVertex::Vertex* Application::Render::Scene::get_ptr() const
{
	return this->pVBuffer->data;
}

Application::Render::Scene::~Scene()
{
	delete this->pVBuffer;
}
