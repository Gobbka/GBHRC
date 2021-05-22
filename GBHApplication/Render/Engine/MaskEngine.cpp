#include "MaskEngine.h"

#include "../../../GBHRC/includes/logger.h"


Application::Render::MaskEngine::MaskEngine(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTarget,UINT width,UINT height)
{
	DEBUG_LOG("W:" <<std::dec<< width << " H: " << height);
	
	this->pDevice = pDevice;
	this->pContext = pContext;

	///
	
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
	depthStencilTextureDesc.Width = width;
	depthStencilTextureDesc.Height = height;
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.ArraySize = 1;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.SampleDesc.Count = 1;
	depthStencilTextureDesc.SampleDesc.Quality = 0;
	depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.CPUAccessFlags = 0;
	depthStencilTextureDesc.MiscFlags = 0;

	HRESULT hr;
	
	hr = this->pDevice->CreateTexture2D(&depthStencilTextureDesc, nullptr, &this->depthStencilBuffer);
	if (FAILED(hr))
		DEBUG_LOG("[D3D]::ERROR CANNOT CREATE STENCIL TEXTURE");

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	
	hr = this->pDevice->CreateDepthStencilView(this->depthStencilBuffer, &descDSV, &this->depthStencilView);
	if (FAILED(hr))
		DEBUG_LOG("[D3D]::ERROR CANNOT CREATE STENCIL VIEW");

	this->pContext->OMSetRenderTargets(1, &pRenderTarget, this->depthStencilView);
	
	D3D11_DEPTH_STENCIL_DESC depthstencildesc{};

	depthstencildesc.DepthEnable = TRUE;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

	depthstencildesc.StencilEnable = TRUE;
	depthstencildesc.StencilReadMask = 0XFF;
	depthstencildesc.StencilWriteMask = 0XFF;

	depthstencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS; //In the default stencil state, always pass, don't even do a comparison function
	depthstencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (WILL NEVER FAIL SO TECHNICALLY IRRELEVANT)
	/*
	Explanation of "depthstencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT; "
	INCREMENT & CLAMP VALUE - IF THE VALUE WAS 0 (DEFAULT), AND WE PASS TEST (WHICH WE WILL SINCE WE USE ALWAYS)
	INCREMENT VALUE OF STENCIL BUFFER BY 1 AND CLAMP. MAX 255 I THINK?
	THE DISCARD DEPTH STENCIL WILL USE THIS VALUE TO COMPARE TO SEE IF A PIXEL HAS BEEN WRITTEN TO IN THAT STENCIL
	BUFFER LOCATION.*/
	depthstencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
	depthstencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (DEPTH IS DISABLED SO SHOULD NEVER FAIL? TECHNICALLY IRRELEVANT)

	// We are not rendering backfaces, so never run any comparison function on backface (D3D11_COMPARISON_NEVER)
	depthstencildesc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	depthstencildesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS
	depthstencildesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS
	depthstencildesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS

	hr = this->pDevice->CreateDepthStencilState(&depthstencildesc, &this->drawState);

	if (FAILED(hr))
		DEBUG_LOG("Failed to create depth stencil state.");

	//Discard blend state (Just need to change a few things from default depth stencil)
	depthstencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS; //ONLY PASS IF THE SOURCE PIXEL VALUE = STENCILREF
	depthstencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (same as default)
	depthstencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (Notice in default we incremented, but in this we don't! We only want to compare to the stencil value written by the previous stencil state)
	depthstencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (same as default)
	
	hr = this->pDevice->CreateDepthStencilState(&depthstencildesc, &this->discardState);

	CD3D11_DEPTH_STENCIL_DESC defstate(D3D11_DEFAULT);
	defstate.DepthFunc = D3D11_COMPARISON_ALWAYS;

	hr = this->pDevice->CreateDepthStencilState(&defstate, &this->disabledState);

	if (FAILED(hr))
	{
		DEBUG_LOG(hr << " Failed to create depth stencil state.");
	}
}

void Application::Render::MaskEngine::clearBuffer() const
{
	this->pContext->ClearDepthStencilView(depthStencilView,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0, 0);
}

void Application::Render::MaskEngine::set_draw_mask() const
{
	this->pContext->OMSetDepthStencilState(this->drawState, 0);
}

void Application::Render::MaskEngine::set_discard_mask() const
{
	this->pContext->OMSetDepthStencilState(this->discardState, 0);
}

void Application::Render::MaskEngine::unset_mask() const
{
	this->pContext->OMSetDepthStencilState(disabledState, 0);
}

ID3D11DepthStencilView* Application::Render::MaskEngine::get_stencil_view() const
{
	return this->depthStencilView;
}
