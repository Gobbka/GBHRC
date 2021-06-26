#include "ConstantBuffer.h"
#include "../../Engine/Engine.h"

void Render::ConstantBuffer::set_projection(DirectX::XMMATRIX mProjection)
{
	_buffer.mProjection = mProjection;
}

void Render::ConstantBuffer::set_alpha(float alpha)
{
	_buffer.alpha = alpha;
}

Render::ConstantBuffer::ConstantBuffer(Application::Render::Engine* engine, DirectX::XMMATRIX mProjection, float alpha)
	:
Bindable(engine),
_buffer({alpha,mProjection})
{
	_d3d_buffer = nullptr;
	
	D3D11_BUFFER_DESC desc{ sizeof(D3DConstantBuffer),D3D11_USAGE_DEFAULT,D3D11_BIND_CONSTANT_BUFFER,0,0,0 };
	D3D11_SUBRESOURCE_DATA sd{ &_buffer,0,0 };

	if(FAILED(_engine->pDevice->CreateBuffer(&desc, &sd, &_d3d_buffer)))
	{
		DEBUG_LOG("CANNOT_CREATE_CONSTANT_BUFFER");
	}
}

void Render::ConstantBuffer::bind()
{
	_engine->pDevContext->VSSetConstantBuffers(0, 1, &_d3d_buffer);
}

void Render::ConstantBuffer::update()
{
	_engine->pDevContext->UpdateSubresource(_d3d_buffer, 0, nullptr, &_buffer, 0, 0);
}
