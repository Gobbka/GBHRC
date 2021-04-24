#include "Transform.h"


#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace,args) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace,args)

void UnityEngine::Transform::rotate(float x, float y, float z)
{
	STATIC_METHOD("UnityEngine.Transform:Rotate()", true,-1);

	void* args[]{ &x,&y,&z };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

void UnityEngine::Transform::lookAt(UnityTypes::Vector3* pos)
{
	// 0x060018EE
	STATIC_METHOD("UnityEngine.Transform:LookAt()", true,1);

	DEBUG_LOG("METHOD: "<< pMethod << " : "<<Mono::mono_method_get_token(pMethod));
	void* args[]{ pos };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

UnityTypes::Vector3* UnityEngine::Transform::get_position()
{
	static auto* pGetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
		"position"
	));

	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pGetPosMethod, this, nullptr, nullptr);
}

void UnityEngine::Transform::set_position(UnityTypes::Vector3* vector)
{
	static auto* pSetPosMethod = Mono::mono_property_get_set_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
		"position"
	));
	void* params[]{ &vector };
	Mono::mono_runtime_invoke(pSetPosMethod, this, params, nullptr);
}

UnityTypes::Vector3* UnityEngine::Transform::get_eulerAngles()
{
	static auto* pGetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
		"eulerAngles"
	));

	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pGetPosMethod, this, nullptr, nullptr);
}
