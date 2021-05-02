#include "Camera.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) auto*mono_context = Mono::Context::get_context();static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_UE_CoreModule(),name, inc_namespace,param_count)
#define DEG_TO_RAD (3.1415 * 2) / 360

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
	auto* nigger = (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
	return nigger;
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

	screen->x = windowWidth / 2 + NDC.x / tan(get_horizontal_fov() / 2) * (float)windowWidth / 2;
	screen->y = windowHeight / 2 - NDC.y / tan(get_horizontal_fov() / 2) * (float)windowWidth / 2;

	//screen->x = NDC.x / tan(get_horizontal_fov() / 2) * (float)windowWidth / 2;
	//screen->y = NDC.y / tan(this->get_horizontal_fov() / 2) * (float)windowWidth / 2;

	screen->z = NDC.z;
	return true;
}

bool UnityEngine::Camera::worldToScreen_beta(Vector3 pos, Vector3* screen, int windowWidth, int windowHeight)
{
	auto* proj_matrix = this->projectionMatrix();
	auto* view_matrix = this->worldToCameraMatrix();


	auto clipCoords = view_matrix->multiply(Vector4{pos.x,pos.y,pos.z,1.0});
	clipCoords = proj_matrix->multiply(clipCoords);

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	
	
	screen->x = ((float)windowWidth / 2 * NDC.x);
	screen->y = ((float)windowHeight / 2 * NDC.y);
	screen->z = clipCoords.w;
	
	DEBUG_LOG("Z: " << clipCoords.z << " W " << clipCoords.w);

	DEBUG_LOG(
		"DEPTH: " << get_depth() <<
		" WIDT: " << this->get_pixelWidth() << " ASPECT: " << this->get_aspect()
	);

	return true;
}

bool UnityEngine::Camera::worldToScreen_alpha(Vector3 pos, Matrix4X4* trans, Vector3* screen, int windowWidth, int windowHeight)
{
	auto* v_matrix = this->worldToCameraMatrix();
	auto* p_matrix = this->projectionMatrix();

	auto clip = v_matrix->multiply(pos);
	clip = p_matrix->multiply(clip);

	screen->x = clip.x * (float)windowWidth / 2 - (float)windowWidth / 2;
	screen->y = clip.y * (float)windowHeight / 2 - (float)windowHeight / 2;

	DEBUG_LOG(
		"DEPTH: " << get_depth() <<
		" WIDT: " << this->get_pixelWidth() << " ASPECT: " << this->get_aspect() << " ORTHO: " << this->is_orthographic() << " ORTHO_SIZE: "
		<< this->get_orthographicSize() << " FOV: " << this->get_fieldOfView()
	);

	return true;
}

int UnityEngine::Camera::get_scaledPixelWidth()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"scaledPixelWidth"
	));

	return ((MonoInt*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
}

int UnityEngine::Camera::get_pixelWidth()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"pixelWidth"
	));

	return ((MonoInt*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
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

	return ((MonoBool*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
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

	return ((MonoFloat*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
}

float UnityEngine::Camera::get_orthographicSize()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"orthographicSize"
	));

	return ((MonoFloat*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
}

float UnityEngine::Camera::get_aspect()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"aspect"
	));

	return ((MonoFloat*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
}

float UnityEngine::Camera::get_depth()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Camera"),
		"depth"
	));

	return ((MonoFloat*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr))->value;
}

float UnityEngine::Camera::get_horizontal_fov()
{
	float vFOVInRads = this->get_fieldOfView() * DEG_TO_RAD;
	return 2 * atan(tan(vFOVInRads / 2) * this->get_aspect());

}
