#pragma once
#include "d3d11.h"

namespace Application
{
	namespace Render
	{
		class MaskEngine
		{
			ID3D11DepthStencilState* drawState;
			ID3D11DepthStencilState* discardState;
			ID3D11DepthStencilState* disabledState;
			ID3D11DepthStencilState* current_state;
			
			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;

			ID3D11Device* pDevice;
			ID3D11DeviceContext* pContext;
		private:
			
			
		public:
			MaskEngine(ID3D11Device*pDevice,ID3D11DeviceContext*pContext,ID3D11RenderTargetView*pRenderTarget, UINT width, UINT height);

			void clearBuffer() const;

			void set_draw_mask();
			void set_discard_mask();
			void unset_mask();
			void reset_mask();

			ID3D11DepthStencilState* get_drawState() CONST
			{
				return this->drawState;
			}
			ID3D11DepthStencilState* get_discardState() CONST
			{
				return this->discardState;
			}
			ID3D11DepthStencilState* get_disabledState() CONST
			{
				return this->disabledState;
			}

			ID3D11DepthStencilState* get_current_state() CONST
			{
				return this->current_state;
			}

			ID3D11DepthStencilView* get_stencil_view() CONST;
		};
	}
}
