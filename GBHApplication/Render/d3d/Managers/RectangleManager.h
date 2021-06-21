#pragma once
#include "../Vertex.h"

namespace Application
{

	namespace Managers
	{
		class Rectangle
		{
		public:
			static const UINT vertex_size = 4;
			
			static void set_rect(GVertex::Vertex* ptr, float x, float y, float width, float height)
			{
				ptr[0].pos = DirectX::XMFLOAT3(x, y, 1.f);
				ptr[1].pos = DirectX::XMFLOAT3(x + width, y, 1.f);
				ptr[2].pos = DirectX::XMFLOAT3(x, y - height, 1.f);
				ptr[3].pos = DirectX::XMFLOAT3(x + width, y-height, 1.f);
			}

			static void set_color(GVertex::Vertex* ptr, float r, float g, float b)
			{
				for (int i = 0; i < 4; i++)
				{
					ptr[i].color = DirectX::XMFLOAT3{ r,g,b };
				}
			}

			static void set_color(GVertex::Vertex* ptr, Render::Color color)
			{
				for (int i = 0; i < 4; i++)
				{
					ptr[i].color = DirectX::XMFLOAT3{ color.r,color.g,color.b};
				}
			}
		};
	}
}