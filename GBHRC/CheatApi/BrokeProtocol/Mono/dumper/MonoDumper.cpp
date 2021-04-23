#include "MonoDumper.h"


#include "../Mono.h"
#include "../../../../includes/logger.h"


void Mono::Dumper::dump_class(MonoClass* klass)
{
	void* pointer = NULL;
	Mono::MonoClassField* field = NULL;

	DEBUG_LOG("====== " << Mono::mono_class_get_name(klass) << " ======");
	while ((field = Mono::mono_class_get_fields(klass, &pointer)))
	{
		DEBUG_LOG("0x" << std::hex << mono_field_get_offset(field) << " : " << mono_field_get_name(field));
	}
	DEBUG_LOG("=========================");
}

void Mono::Dumper::dump_object(MonoObject* object)
{
	Dumper::dump_class(Mono::mono_object_get_class(object));
}
