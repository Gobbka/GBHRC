#include "Camera.h"
#include "../../Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace,param_count)

UnityTypes::Vector3* UnityEngine::Camera::WorldToScreenPoint(UnityTypes::Vector3* pos)
{
	STATIC_METHOD("UnityEngine.Camera:WorldToScreenPoint()", true,1);
	void* args[]{ pos };
	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

UnityTypes::Vector3* UnityEngine::Camera::WorldToViewportPoint(UnityTypes::Vector3* pos)
{
	STATIC_METHOD("UnityEngine.Camera:WorldToViewportPoint()", true, 1);
	void* args[]{ pos };
	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

Matrix4X4* UnityEngine::Camera::projectionMatrix()
{
	// projectionMatrix

	static auto* pSetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Camera"),
		"projectionMatrix"
	));

	return(Matrix4X4*)Mono::mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

Matrix4X4* UnityEngine::Camera::GetStereoViewMatrix()
{

	STATIC_METHOD("UnityEngine.Camera:GetStereoViewMatrix()", true, 1);
	int gakba = 0;
	void* args[]{ &gakba };
	return(Matrix4X4*)Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

Matrix4X4* UnityEngine::Camera::cameraToWorldMatrix()
{
	static auto* pSetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Camera"),
		"cameraToWorldMatrix"
	));

	return(Matrix4X4*)Mono::mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

Matrix4X4* UnityEngine::Camera::worldToCameraMatrix()
{
	static auto* pSetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Camera"),
		"worldToCameraMatrix"
	));

	return(Matrix4X4*)Mono::mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}
