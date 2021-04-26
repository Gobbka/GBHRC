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
