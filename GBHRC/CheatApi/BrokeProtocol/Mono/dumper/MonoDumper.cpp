#include "MonoDumper.h"


#include "../Mono.h"
#include "../../../../includes/logger.h"

void Mono::Dumper::dump_class(MonoClass* klass)
{
	auto* mono_context = Mono::Context::get_context();
	void* pointer = NULL;
	Mono::MonoClassField* field = NULL;

	DEBUG_LOG("====== " << mono_context->mono_class_get_name(klass) << " ======");
	while ((field = mono_context->mono_class_get_fields(klass, &pointer)))
	{
		DEBUG_LOG("0x" << std::hex << mono_context->mono_field_get_offset(field) << " : " << mono_context->mono_field_get_name(field));
	}
	DEBUG_LOG("=========================");
}

void Mono::Dumper::dump_object(MonoObject* object)
{
	auto* mono_context = Mono::Context::get_context();
	Dumper::dump_class(mono_context->mono_object_get_class(object));
}
