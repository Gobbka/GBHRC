#pragma once
#include "../MonoDefs.h"

namespace Mono
{
	namespace Dumper
	{
		void dump_method(MonoMethod* method);
		void dump_class(MonoClass* klass);
		void dump_object(MonoObject*object);
	}
}
