#pragma once
#include "../../UnityTypes.h"
#include "../../../Tools/3dMatrix.h"
namespace UnityEngine
{
	class Camera
	{
	public:
		static Camera* main();
		static Camera* current();
		
		UnityTypes::Vector3* WorldToScreenPoint(UnityTypes::Vector3* pos);
		UnityTypes::Vector3* WorldToViewportPoint(UnityTypes::Vector3* pos);

		void WorldToViewportPoint_Injected(UnityTypes::Vector3* pos, UnityTypes::Vector3* out);
		
		Matrix4X4* projectionMatrix();
		Matrix4X4* GetStereoViewMatrix();
		Matrix4X4* cameraToWorldMatrix();
		Matrix4X4* worldToCameraMatrix();

		void set_fieldOfView(float new_f);
		bool is_orthographic();
		void set_orthographicSize(float new_f);
		float get_fieldOfView();
	};
}

