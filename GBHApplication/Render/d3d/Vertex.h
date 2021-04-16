#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace GVertex
{
	struct Vertex
	{

		Vertex();
		Vertex(float x, float y, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

	const D3D11_INPUT_ELEMENT_DESC Layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	struct VertexBuffer
	{
		ID3D11Buffer* buffer = nullptr;
		GVertex::Vertex* data = nullptr;
		UINT size = 0;

		ID3D11Buffer* get_buffer() const;

		HRESULT create(ID3D11Device* pDevice, GVertex::Vertex* data, UINT size);

		~VertexBuffer();
	};

}
