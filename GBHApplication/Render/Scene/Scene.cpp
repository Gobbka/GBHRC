#include "Scene.h"

#include "../../Application.h"

#define DRAW_ASSERT if(this->hidden==true) return;

void Application::Render::Scene::alloc_vbuffer(Render::Engine* pEngine)
{
	delete this->pVBuffer;
	UINT size = 0;

	for (auto* element : this->pElements)
	{
		size += element->size();
	}

	this->pVBuffer = pEngine->make_vertex_buffer(size);
}

void Application::Render::Scene::update(ID3D11DeviceContext* pContext) const
{
	DRAW_ASSERT

	D3D11_MAPPED_SUBRESOURCE subdata;
	pContext->Map(this->pVBuffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);
	memcpy(subdata.pData, this->pVBuffer->data, this->pVBuffer->size * sizeof(GVertex::Vertex));
	pContext->Unmap(this->pVBuffer->buffer, 0);
}

void Application::Render::Scene::render(ID3D11DeviceContext* pContext)
{
	DRAW_ASSERT

	UINT stride = sizeof(GVertex::Vertex);
	UINT offset = 0;

	pContext->IASetVertexBuffers(0, 1, &this->pVBuffer->buffer, &stride, &offset);

	for (auto* element : this->pElements)
	{
		element->__draw(pContext);
	}

}

void Application::Render::Scene::set_resolution(Resolution resolution)
{
	this->resolution = resolution;
}

void Application::Render::Scene::add_markup_elements(UINT count, Application::UI::IElement* elements, ...)
{
	va_list v1;
	va_start(v1, count);

	for (UINT i = 0; i < count; i++)
	{
		this->pElements.push_back(va_arg(v1, Application::UI::IElement*));
	}
}

GVertex::Vertex* Application::Render::Scene::get_ptr() const
{
	return this->pVBuffer->data;
}

Application::Render::Scene::~Scene()
{
	delete this->pVBuffer;
}
