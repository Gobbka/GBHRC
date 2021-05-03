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
		
		bool worldToScreen(Vector3 pos,Vector3* screen, int windowWidth, int windowHeight);
		bool worldToScreen_beta(Vector3 pos,Vector3* screen, int windowWidth, int windowHeight);
		bool worldToScreen_alpha(Vector3 pos, Matrix4X4*trans,Vector3* screen, int windowWidth, int windowHeight);

		int get_scaledPixelWidth();
		int get_pixelWidth();
		int get_pixelHeight();
		
		void WorldToViewportPoint_Injected(UnityTypes::Vector3* pos, UnityTypes::Vector3* out);
		
		Matrix4X4* projectionMatrix();
		Matrix4X4* GetStereoViewMatrix();
		Matrix4X4* cameraToWorldMatrix();
		Matrix4X4* worldToCameraMatrix();

		void set_fieldOfView(float new_f);
		bool is_orthographic();
		void set_orthographicSize(float new_f);
		float get_fieldOfView();
		float get_orthographicSize();
		float get_aspect();
		float get_depth();

		float get_horizontal_fov();
	};
}

