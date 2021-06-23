#include "Transform.h"
#include "../../../../includes/logger.h"
#include "../../Mono/Mono.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace,args) auto*mono_context=Mono::Context::get_context();static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_UE_CoreModule(),name, inc_namespace,args)

void UnityEngine::Transform::rotate(float x, float y, float z)
{
	STATIC_METHOD("UnityEngine.Transform:Rotate()", true, -1);

	void* args[]{ &x,&y,&z };
	mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

void UnityEngine::Transform::lookAt(Transform* pos)
{
	STATIC_METHOD("UnityEngine.Transform:LookAt()", true, 1);
	void* args[]{ pos };
	mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

Matrix4X4* UnityEngine::Transform::localToWorldMatrix()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Transform"),
		"localToWorldMatrix"
	));

	return(Matrix4X4*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

UnityTypes::Vector3* UnityEngine::Transform::InverseTransformPoint(UnityTypes::Vector3* pos)
{
	STATIC_METHOD("UnityEngine.Transform:InverseTransformPoint()", true, 1);
	void* args[]{ pos };

	return (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

UnityTypes::Vector3* UnityEngine::Transform::get_position()
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pGetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Transform"),
		"position"
	));

	return (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pGetPosMethod, this, nullptr, nullptr);
}

void UnityEngine::Transform::set_position(UnityTypes::Vector3* vector)
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pSetPosMethod = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Transform"),
		"position"
	));
	void* params[]{ vector };
	mono_context->mono_runtime_invoke(pSetPosMethod, this, params, nullptr);
}

UnityTypes::Vector3* UnityEngine::Transform::get_eulerAngles()
{
	auto* mono_context = Mono::Context::get_context();
	static auto* pGetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Transform"),
		"eulerAngles"
	));

	return (UnityTypes::Vector3*)mono_context->mono_runtime_invoke(pGetPosMethod, this, nullptr, nullptr);
}
