#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "../Bindable.h"

namespace Render
{


	class ConstantBuffer : Application::Render::Bindable
	{
	private:
		struct D3DConstantBuffer
		{
			float alpha;
			DirectX::XMMATRIX mProjection;
		};

		ID3D11Buffer* _d3d_buffer;
		D3DConstantBuffer _buffer;
	public:
		void set_projection(DirectX::XMMATRIX mProjection);
		void set_alpha(float alpha);
		
		ConstantBuffer(Application::Render::Engine*engine,DirectX::XMMATRIX mProjection,float alpha);
		
		void bind() override;
		void update();
	};
}
