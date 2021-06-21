#pragma once
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <vector>


#include "MaskEngine.h"
#include "../Render.h"
#include "../d3d/Vertex.h"

namespace Application
{
	namespace Render
	{
		class BlendEngine;
		class CanvasScene;
		
		class Engine
		{
		private:
			HWND window;
		public:
			ID3D11Device* pDevice;
			ID3D11DeviceContext* pDevContext;
			DirectX::SpriteBatch* get_batch() const;
			MaskEngine* get_mask() const;
		private:
			ID3D11RenderTargetView* pRenderTargetView;
			//
			ID3D11VertexShader* pVertexShader = nullptr;
			ID3D11InputLayout* pVertexLayout = nullptr;
			ID3D11PixelShader* pPixelShader = nullptr;
			//
			ID3D11Buffer* pConstantBuffer = nullptr;
			//
			DirectX::XMMATRIX mOrtho;
			
			DirectX::SpriteBatch* spriteBatch;
			
			D3D11_VIEWPORT pViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE]{ 0 };

			MaskEngine* mask_engine;
			BlendEngine* blend_engine;
		private:
			bool initialize();
			bool create_const_buffer();
			ID3DBlob* create_vs_shader();
			ID3DBlob* create_ps_shader(ID3DBlob* blob);
			void apply_constant_buffer(ConstantBuffer constant_buffer);

			DirectX::XMMATRIX get_ortho_matrix();
			ID3D11RenderTargetView* get_render_target(IDXGISwapChain* pSwap) const;
			static Application::Render::Resolution get_resolution(HWND hwnd);
			//
			std::vector<Application::Render::CanvasScene*> pScenes;

		public:
			void set_vbuffer(GVertex::VertexBuffer* buffer);
			void render_prepare();

			void set_shaders();

			DirectX::SpriteFont* create_font(void* font_source,UINT source_size);
			
			Engine(HWND hwnd, ID3D11Device* pDevice, IDXGISwapChain* pSwapChain);
			Engine* append_scene(Application::Render::CanvasScene* scene);

			//void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);
			void update_scene();
			void present();

			GVertex::VertexBuffer* make_vertex_buffer(UINT size) const;

			static bool compile_shader(const char* szShader, const char* szEntrypoint, const char* szTarget, ID3D10Blob** pBlob);
		};
	}
}
