#include "Vertex.h"

GVertex::Vertex::Vertex()
{
	this->pos = DirectX::XMFLOAT3{ 0.f,0.f,1.f };
	this->color = DirectX::XMFLOAT4{ 0.f,0.f,0.f,0.f };
}

GVertex::Vertex::Vertex(float x, float y, float r, float g, float b, float a)
{
	this->pos = DirectX::XMFLOAT3{ x,y,1.f };
	this->color = DirectX::XMFLOAT4{ r,g,b,a };
}

ID3D11Buffer* GVertex::VertexBuffer::get_buffer() const
{
	return this->buffer;
}

HRESULT GVertex::VertexBuffer::create(ID3D11Device* pDevice, GVertex::Vertex* data, UINT size)
{
	this->size = size;
	this->data = data;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(GVertex::Vertex) * size;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = sizeof(GVertex::Vertex);

	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(subresourceData));
	subresourceData.pSysMem = data;

	return pDevice->CreateBuffer(&vertexBufferDesc, &subresourceData, &buffer);
}

GVertex::VertexBuffer::~VertexBuffer()
{
	if (buffer)
		buffer->Release();
	delete[] data;
}
