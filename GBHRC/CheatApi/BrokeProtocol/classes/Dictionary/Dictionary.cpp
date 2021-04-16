#include "Dictionary.h"

void Dictionary::copy_to(Mono::MonoArray* array, int index)
{
	void* args[2];

	args[0] = array;
	args[1] = &index;

	Mono::mono_runtime_invoke(
		Mono::mono_class_get_method_from_name(
			Mono::mono_class_from_name(Mono::get_mscorlib(),"System.Collections.Generic","Dictionary"),
			"CopyTo",
			-1
		),
		this,
		args,
		nullptr
	);
}
