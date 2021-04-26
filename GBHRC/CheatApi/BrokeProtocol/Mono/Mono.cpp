#include "Mono.h"


#include "../BPStructs.h"
#include "../../../includes/logger.h"

using namespace Mono;

void Context::mono_field_from_name_get_value(MonoObject* object, const char* name, void* pValue)
{
	auto* pClass = mono_object_get_class(object);
	auto* field = mono_class_get_field_from_name(pClass, name);
	mono_field_get_value(object, field, pValue);
}


void Context::mono_get_static_field_value(MonoClass* klass, UINT token,void*value)
{
	auto* vTable = Context::mono_class_vtable(Context::mono_get_root_domain(), klass);
	
	auto* static_class = Context::mono_object_get_class((Mono::MonoObject*)vTable);
	
	auto* pstatic_field = Context::mono_class_get_field(static_class, token);
	
	Context::mono_field_static_get_value(vTable, pstatic_field, value);
}



Mono::MonoMethod* Context::mono_get_method_from_image(MonoImage* image, const char* desc, bool include_namespace, int param_count)
{
	auto* method_desc = Context::mono_method_desc_new(desc, include_namespace);

	auto* pClass = Context::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
	auto* method = Context::mono_class_get_method_from_name(pClass, method_desc->method_name, param_count);

	Context::mono_method_desc_free(method_desc);

	return method;
}

void Context::mono_print_system_exception(void* exception)
{
	auto* klass = Context::mono_class_from_name(get_mscorlib(), "System", "Exception");
	auto* field = Context::mono_class_get_field_from_name(klass, "_message");
	UnityTypes::String* value;
	mono_field_get_value((MonoObject*)exception, field, &value);
	DEBUG_LOG("<ERROR> "<<(char*)(value->array));
}

Mono::MonoObject* Context::create_csharp_string(char* ptr)
{
	auto* image = get_mscorlib();
	auto* pClass = Context::mono_class_from_name(image, "System.Runtime.InteropServices", "Marshal");
	auto* method = mono_class_get_method_from_name(pClass, "PtrToStringUTF8", -1);

	void* params[2];
	params[0] = &ptr;
	params[1] = new int(strlen(ptr));

	MonoObject* excepion = nullptr;

	auto* nigger = (MonoObject*)Context::mono_runtime_invoke(method, NULL, params, &excepion);

	if (excepion != nullptr)
	{
		DEBUG_LOG("NIGGER ERROR");
	}

	return nigger;
}

Mono::MonoClass* Context::get_object_class()
{
	return mono_class_from_name(get_mscorlib(), "System", "Object");
}

Mono::MonoImage* Context::get_script_image()
{
	static MonoImage* image = Context::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
	
	return image;
}

Mono::MonoImage* Context::get_mscorlib()
{
	static MonoImage* image = image = Context::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\mscorlib.dll");

	return image;
}

Mono::MonoImage* Context::get_UE_CoreModule()
{
	static MonoImage* image = Context::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\UnityEngine.CoreModule.dll");

	return image;
}

Context::Context()
{
	vTable::implement();
}

Mono::Context* Context::get_context()
{
	static Mono::Context* context = new Mono::Context();
	return context;
}

