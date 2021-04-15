#pragma once
#include "../../Mono.h"

namespace Mono
{
	namespace ScriptImage
	{
		MonoMethod* mono_get_method_from_name(const char* name, bool include_namespace);
	}
}
