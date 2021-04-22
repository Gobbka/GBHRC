#include "Camera.h"
#include "../../Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace)

UnityTypes::Vector3* UnityEngine::Camera::WorldToScreenPoint(UnityTypes::Vector3* pos)
{
	 // WorldToScreenPoint
	STATIC_METHOD("UnityEngine.Camera:WorldToScreenPoint()", true);
	void* args[]{ pos };
	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}
