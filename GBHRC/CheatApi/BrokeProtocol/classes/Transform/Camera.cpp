#include "Camera.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) auto*mono_context = Mono::Context::get_context();static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_UE_CoreModule(),name, inc_namespace,param_count)
#define RAD_TO_DEG (3.1415 * 2) / 360

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

bool UnityEngine::Camera::worldToScreen(Vector3 pos, Vector3* screen, int windowWidth, int windowHeight)
{
	Vector4 clipCoords{};
	{
		// view matrix
		auto* pmatrix = this->worldToCameraMatrix();
		clipCoords.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 + pos.z * pmatrix->m32 + pmatrix->m33;
		if (clipCoords.w < 0.01f)
			return false;

		clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pmatrix->m03;
		clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pmatrix->m13;
		clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pmatrix->m23;
	}
	{
		// mul by projection matrix
		auto* pProjectMatrix = this->projectionMatrix();
		clipCoords.x = clipCoords.x * pProjectMatrix->m00 + clipCoords.y * pProjectMatrix->m01;
		clipCoords.y = clipCoords.x * pProjectMatrix->m10 + clipCoords.y * pProjectMatrix->m11;
	}

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	// эта херь выдаёт нереально агромные результаты
	//screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	//screen->y = (windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	screen->x = windowWidth/2 + NDC.x/tan(get_horizontal_fov()/2)*(float)windowWidth/2;
	screen->y = windowHeight/2 - NDC.y/tan(get_horizontal_fov()/2)*(float)windowWidth/2;

	//screen->x = NDC.x / tan(get_horizontal_fov() / 2) * (float)windowWidth / 2;
	//screen->y = NDC.y / tan(this->get_horizontal_fov() / 2) * (float)windowWidth / 2;
	
	screen->z = NDC.z;
	return true;
}

bool UnityEngine::Camera::worldToScreen_beta(Vector3 pos, Vector3* screen, int windowWidth, int windowHeight)
{
	auto* proj_matrix = this->projectionMatrix();
	auto* view_matrix = this->worldToCameraMatrix();

	Matrix4X4 viewProjMatrix = *view_matrix;

	auto clipCoords = viewProjMatrix.multiply(pos);
	clipCoords = proj_matrix->multiply(clipCoords);

	screen->x = clipCoords.x;
	screen->y = clipCoords.y;
	//screen->x = round(
	//	((nigger_point.x + 1) / 2.0) * windowWidth
	//);
	//screen->y = round(
	//	((1 - nigger_point.y) / 2.0) * windowHeight
	//);

	return true;

	//   Matrix4X4 viewProjectionMatrix = projectionMatrix * viewMatrix;
	//   //transform world to clipping coordinates
	//   point3D = viewProjectionMatrix.multiply(point3D);
	//   int winX = (int)Math.round(((point3D.getX() + 1) / 2.0) *
	//   	width);
	//   //we calculate -point3D.getY() because the screen Y axis is
	//   //oriented top->down 
	//   int winY = (int)Math.round(((1 - point3D.getY()) / 2.0) *
	//   	height);
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

float UnityEngine::Camera::get_aspect()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"aspect"
	));

	return (float)(__int64)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

float UnityEngine::Camera::get_horizontal_fov()
{
	float vFOVInRads = this->get_fieldOfView() * RAD_TO_DEG;
	return 2 * atan(tan(vFOVInRads / 2) * this->get_aspect());
	
}
