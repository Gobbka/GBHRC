#include "UnityTypes.h"

#include "../../includes/logger.h"
#include "Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace,param_count)

UnityTypes::Vector3* UnityTypes::Vector3::make(float x, float y, float z)
{
	auto* mono_context = Mono::Context::get_context();
	auto* vector = (Vector3*)mono_context->mono_object_new(mono_context->mono_get_root_domain(), mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Vector3"));
	vector->x = x; vector->y = y; vector->z = z;
	return vector;
}

float UnityTypes::Vector3::distanceTo(UnityTypes::Vector3* vector) const
{
	return sqrt(pow(vector->x - this->x, 2) + pow(vector->y - this->y, 2) + pow(vector->z - this->z, 2));
}
