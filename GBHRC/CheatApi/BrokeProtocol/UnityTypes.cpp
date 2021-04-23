#include "UnityTypes.h"

#include "../../includes/logger.h"
#include "Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace,param_count)

UnityTypes::Vector3* UnityTypes::Vector3::make(float x, float y, float z)
{
	auto* vector = (Vector3*)Mono::mono_object_new(Mono::mono_get_root_domain(), Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Vector3"));
	vector->x = x; vector->y = y; vector->z = z;
	return vector;
}
