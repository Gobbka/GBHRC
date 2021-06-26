#include "BlendEngine.h"
#include "Engine.h"
#include "../../Render/d3d/Buffers/ConstantBuffer.h"

Application::Render::BlendEngine::BlendEngine(Render::Engine* engine)
{

	this->engine = engine;
	
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

	blendDesc.RenderTarget[0] = rtbd;

	if(FAILED(engine->pDevice->CreateBlendState(&blendDesc, &this->blend_state)))
	{
		DEBUG_LOG("[D3D] CANNOT CREATE BLEND STATE");
	}
}

void Application::Render::BlendEngine::set_blend_state()
{
	this->engine->pDevContext->OMSetBlendState(this->blend_state, NULL, 0xFFFFFFFF);
}

void Application::Render::BlendEngine::set_alpha(::Render::ConstantBuffer* cb,float alpha)
{
	cb->set_alpha(alpha);
	cb->update();
}
