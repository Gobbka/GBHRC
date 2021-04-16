#pragma once
#include <DirectXMath.h>

struct ConstantBuffer
{
	float xOffset;
	float yOffset;
	DirectX::XMMATRIX mProjection;
};

