#include "Transform.h"


#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace)

void UnityEngine::Transform::rotate(float x, float y, float z)
{
	STATIC_METHOD("UnityEngine.Transform:Rotate()", true);

	void* args[]{ &x,&y,&z };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

void UnityEngine::Transform::lookAt(UnityTypes::Vector3* pos)
{
	// 0x060018EE
	STATIC_METHOD("UnityEngine.Transform:LookAt()", true, 1);
	void* args[]{ pos };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}
