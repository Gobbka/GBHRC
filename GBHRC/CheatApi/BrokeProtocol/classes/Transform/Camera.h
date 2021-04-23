#pragma once
#include "../../UnityTypes.h"
#include "../../../Tools/3dMatrix.h"
namespace UnityEngine
{
	class Camera
	{
	public:
		UnityTypes::Vector3* WorldToScreenPoint(UnityTypes::Vector3* pos);
		UnityTypes::Vector3* WorldToViewportPoint(UnityTypes::Vector3* pos);
		Matrix4X4* projectionMatrix();
		Matrix4X4* GetStereoViewMatrix();
		Matrix4X4* cameraToWorldMatrix();
		Matrix4X4* worldToCameraMatrix();
	};
}

