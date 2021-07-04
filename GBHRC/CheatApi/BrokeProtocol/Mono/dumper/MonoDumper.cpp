#include "MonoDumper.h"


#include "../Mono.h"
#include "../../../../includes/logger.h"

IMPORT_LOGGER();

void Mono::Dumper::dump_method(MonoMethod* method)
{
	auto* mono_context = Mono::Context::get_context();

	DEBUG_LOG("===== " << mono_context->mono_method_get_name(method) << " =====");
	DEBUG_LOG("NATIVE PTR: "<<mono_context->mono_compile_method(method));
}

void Mono::Dumper::dump_class(MonoClass* klass)
{
	
	auto* mono_context = Mono::Context::get_context();

	auto* nigger = mono_context->mono_class_get_parent(klass);
	if (nigger != nullptr)
		dump_class(nigger);
	void* pointer = NULL;
	Mono::MonoClassField* field = NULL;

	DEBUG_LOG("====== " << mono_context->mono_class_get_name(klass) << " ======");
	while ((field = mono_context->mono_class_get_fields(klass, &pointer)))
	{
		DEBUG_LOG("0x" << std::hex << mono_context->mono_field_get_offset(field) << " : " << mono_context->mono_field_get_name(field));
	}
	DEBUG_LOG("==> SIZE : 0x" << std::hex << mono_context->mono_class_instance_size(klass));
	DEBUG_LOG("=========================");
}

void Mono::Dumper::dump_object(MonoObject* object)
{
	auto* mono_context = Mono::Context::get_context();
	
	Dumper::dump_class(mono_context->mono_object_get_class(object));
}
