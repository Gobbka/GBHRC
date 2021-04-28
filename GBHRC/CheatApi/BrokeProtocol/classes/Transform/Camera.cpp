#include "Camera.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) auto*mono_context = Mono::Context::get_context();static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_UE_CoreModule(),name, inc_namespace,param_count)

UnityEngine::Camera* UnityEngine::Camera::main()
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"main"
	));

	return (Camera*)mono_context->mono_runtime_invoke(pSetPosMethod, nullptr, nullptr, nullptr);
}

UnityEngine::Camera* UnityEngine::Camera::current()
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"current"
	));

	return (Camera*)mono_context->mono_runtime_invoke(pSetPosMethod, nullptr, nullptr, nullptr);
}

UnityTypes::Vector3* UnityEngine::Camera::WorldToScreenPoint(UnityTypes::Vector3* pos)
{
	STATIC_METHOD("UnityEngine.Camera:WorldToScreenPoint()", true, 1);
	void* args[]{ pos };
	return (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

UnityTypes::Vector3* UnityEngine::Camera::WorldToViewportPoint(UnityTypes::Vector3* pos)
{
	STATIC_METHOD("UnityEngine.Camera:WorldToViewportPoint()", true, 1);
	void* args[]{ pos };
	return (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

bool UnityEngine::Camera::worldToScreen(Vector3 pos, POINT* screen, int windowWidth, int windowHeight)
{
	//      auto& matrix = g_pEngine->WorldToScreenMatrix();
	        
	//      int ScrW, ScrH;
	//      g_pEngine->GetScreenSize(ScrW, ScrH);
	        
	//      float w = matrix[3][0] * vOrigin[0] + matrix[3][1] * vOrigin[1] + matrix[3][2] * vOrigin[2] + matrix[3][3];
	//      if (w > 0.01)
	//      {
	//      	float inverseWidth = 1 / w;
	//      	vScreen.x = (ScrW / 2) + (0.5 * ((matrix[0][0] * vOrigin[0] + matrix[0][1] * vOrigin[1] + matrix[0][2] * vOrigin[2] + matrix[0][3]) * inverseWidth) * ScrW + 0.5);
	//      	vScreen.y = (ScrH / 2) - (0.5 * ((matrix[1][0] * vOrigin[0] + matrix[1][1] * vOrigin[1] + matrix[1][2] * vOrigin[2] + matrix[1][3]) * inverseWidth) * ScrH + 0.5);
	//      	vScreen.z = 0;
	//      	return true;
	//      }
	//      return false;

	Vector4 clipCoords;
	{
		auto* pmatrix = this->worldToCameraMatrix();
		clipCoords.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 + pos.z * pmatrix->m32 + pmatrix->m33;
		if (clipCoords.w < 0.01f)
			return false;
		
		clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pmatrix->m03;
		clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pmatrix->m13;
		//clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pmatrix->m23;
	}
	{
		auto* pProjectMatrix = this->projectionMatrix();
		clipCoords.x = clipCoords.x * pProjectMatrix->m00 + clipCoords.y * pProjectMatrix->m01;
		clipCoords.y = clipCoords.x * pProjectMatrix->m10 + clipCoords.y * pProjectMatrix->m11;
	}
	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;
	
	//screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	//screen->y = (windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	screen->x = (windowWidth/2) + NDC.x;
	screen->y = NDC.y;
	return true;
}

void UnityEngine::Camera::WorldToViewportPoint_Injected(UnityTypes::Vector3* pos, UnityTypes::Vector3* out)
{
	STATIC_METHOD("UnityEngine.Camera:WorldToViewportPoint_Injected()", true, 3);
	int nigger = 0x2;
	void* args[]{ pos,&nigger,out };
	mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

Matrix4X4* UnityEngine::Camera::projectionMatrix()
{
	// projectionMatrix
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"projectionMatrix"
	));

	return(Matrix4X4*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

Matrix4X4* UnityEngine::Camera::GetStereoViewMatrix()
{

	STATIC_METHOD("UnityEngine.Camera:GetStereoViewMatrix()", true, 1);
	int gakba = 0;
	void* args[]{ &gakba };
	return(Matrix4X4*)mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

Matrix4X4* UnityEngine::Camera::cameraToWorldMatrix()
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"cameraToWorldMatrix"
	));

	return(Matrix4X4*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

Matrix4X4* UnityEngine::Camera::worldToCameraMatrix()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"worldToCameraMatrix"
	));

	return(Matrix4X4*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

void UnityEngine::Camera::set_fieldOfView(float new_f)
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"fieldOfView"
	));
	void* params[]{ &new_f };
	mono_context->mono_runtime_invoke(pSetPosMethod, this, params, nullptr);
}

bool UnityEngine::Camera::is_orthographic()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"orthographic"
	));

	return (bool)(__int64)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

void UnityEngine::Camera::set_orthographicSize(float new_f)
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"orthographicSize"
	));
	void* params[]{ &new_f };
	mono_context->mono_runtime_invoke(pSetPosMethod, this, params, nullptr);
}

float UnityEngine::Camera::get_fieldOfView()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"fieldOfView"
	));

	return (float)(__int64)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

float UnityEngine::Camera::get_orthographicSize()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"orthographicSize"
	));

	return (float)(__int64)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}
