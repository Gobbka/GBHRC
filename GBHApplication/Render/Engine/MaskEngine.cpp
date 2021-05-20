#include "MaskEngine.h"

#include "../../../GBHRC/includes/logger.h"


Application::Render::MaskEngine::MaskEngine(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,UINT width,UINT height)
{
	DEBUG_LOG("MAKING MASK'S...");

	this->pDevice = pDevice;
	this->pContext = pContext;

	///
	///
	///
	
	CD3D11_TEXTURE2D_DESC depthStencilTextureDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, width, height);
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	HRESULT hr;
	
	hr = this->pDevice->CreateTexture2D(&depthStencilTextureDesc, NULL, &this->depthStencilBuffer);
	if (FAILED(hr))
		DEBUG_LOG("CANNOT CREATE STENCIL TEXTURE");
	
	hr = this->pDevice->CreateDepthStencilView(this->depthStencilBuffer, NULL, &this->depthStencilView);
	if (FAILED(hr))
		DEBUG_LOG("CANNOT CREATE STENCIL BUFFER");

	CD3D11_DEPTH_STENCIL_DESC drawMaskedDesc(D3D11_DEFAULT);
	
	#pragma region draw mask initing
	drawMaskedDesc.DepthEnable = false;
	drawMaskedDesc.StencilEnable = true;

	drawMaskedDesc.BackFace
		= D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_COMPARISON_NEVER };
	drawMaskedDesc.FrontFace
		= D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_INCR_SAT,D3D11_COMPARISON_ALWAYS };
	#pragma endregion 

	CD3D11_DEPTH_STENCIL_DESC applyMaskDesc(D3D11_DEFAULT);
	#pragma region apply mask initing
	applyMaskDesc.StencilEnable = true;
	applyMaskDesc.DepthEnable = false;
	applyMaskDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	
	applyMaskDesc.BackFace
		= D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_COMPARISON_NEVER };
	applyMaskDesc.FrontFace
		= D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,D3D11_COMPARISON_LESS };
	#pragma endregion

	CD3D11_DEPTH_STENCIL_DESC defDesc(D3D11_DEFAULT);
	defDesc.DepthEnable = false;
	defDesc.StencilEnable = true;

	if (FAILED(pDevice->CreateDepthStencilState(&defDesc, &this->depthStencilState)))
		DEBUG_LOG("[D3D] CANNOT CREATE STATE");
	
	if(FAILED(pDevice->CreateDepthStencilState(&drawMaskedDesc, &this->drawMask)))
		DEBUG_LOG("[D3D] CANNOT CREATE DRAW MASK");
	
	if(FAILED(pDevice->CreateDepthStencilState(&applyMaskDesc, &this->applyMask)))
		DEBUG_LOG("[D3D] CANNOT CREATE APPLY MASK");
}

void Application::Render::MaskEngine::clearBuffer() const
{
	this->pContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Application::Render::MaskEngine::set_draw_mask() const
{
	this->pContext->OMSetDepthStencilState(this->drawMask, 0);
}

void Application::Render::MaskEngine::set_apply_mask() const
{
	this->pContext->OMSetDepthStencilState(this->applyMask, 0);
}

void Application::Render::MaskEngine::unset_mask()
{
	this->clearBuffer();
	this->pContext->OMSetDepthStencilState(this->depthStencilState, 0);
}

ID3D11DepthStencilView* Application::Render::MaskEngine::get_stencil_view()
{
	return this->depthStencilView;
}
