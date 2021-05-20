#pragma once
#include "d3d11.h"

namespace Application
{
	namespace Render
	{
		class MaskEngine
		{
			ID3D11DepthStencilState* drawMask;
			ID3D11DepthStencilState* applyMask;
			ID3D11DepthStencilState* depthStencilState;
			
			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;

			ID3D11Device* pDevice;
			ID3D11DeviceContext* pContext;
		private:
			
			
		public:
			MaskEngine(ID3D11Device*pDevice,ID3D11DeviceContext*pContext, UINT width, UINT height);

			void clearBuffer() const;

			void set_draw_mask() const;
			void set_apply_mask() const;
			void unset_mask();

			ID3D11DepthStencilState* get_drawMask()
			{
				return this->drawMask;
			};
			ID3D11DepthStencilState* get_applyMask()
			{
				return this->applyMask;
			};

			ID3D11DepthStencilView* get_stencil_view();
		};
	}
}
