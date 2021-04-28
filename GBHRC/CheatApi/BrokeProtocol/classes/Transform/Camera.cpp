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
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords

	Vector4 clipCoords;
	{
		auto* pmatrix = this->worldToCameraMatrix();
		clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pmatrix->m03;
		clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pmatrix->m13;
		clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pmatrix->m23;
		clipCoords.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 + pos.z * pmatrix->m32 + pmatrix->m33;
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
	DEBUG_LOG("VIEW: " << this->get_orthographicSize());
	screen->x = NDC.x;
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
