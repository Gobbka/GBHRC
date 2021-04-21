#include "Transform.h"


#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace)

void Transform::rotate(float x, float y, float z)
{
	STATIC_METHOD("UnityEngine.Transform:Rotate()", true);

	void* args[]{ &x,&y,&z };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}
