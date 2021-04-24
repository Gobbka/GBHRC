#include "Mono.h"


#include "../BPStructs.h"
#include "../../../includes/logger.h"


void Mono::mono_field_from_name_get_value(MonoObject* object, const char* name, void* pValue)
{
	auto* pClass = mono_object_get_class(object);
	auto* field = mono_class_get_field_from_name(pClass, name);
	mono_field_get_value(object, field, pValue);
}


void Mono::mono_get_static_field_value(MonoClass* klass, UINT token,void*value)
{
	auto* vTable = Mono::mono_class_vtable(Mono::mono_get_root_domain(), klass);
	
	auto* static_class = Mono::mono_object_get_class((Mono::MonoObject*)vTable);
	
	auto* pstatic_field = Mono::mono_class_get_field(static_class, token);
	
	Mono::mono_field_static_get_value(vTable, pstatic_field, value);
}



Mono::MonoMethod* Mono::mono_get_method_from_image(MonoImage* image, const char* desc, bool include_namespace, int param_count)
{
	auto* method_desc = Mono::mono_method_desc_new(desc, include_namespace);

	auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
	auto* method = Mono::mono_class_get_method_from_name(pClass, method_desc->method_name, param_count);

	Mono::mono_method_desc_free(method_desc);

	return method;
}

void Mono::mono_print_system_exception(void* exception)
{
	auto* klass = Mono::mono_class_from_name(get_mscorlib(), "System", "Exception");
	auto* field = Mono::mono_class_get_field_from_name(klass, "_message");
	UnityTypes::String* value;
	mono_field_get_value((MonoObject*)exception, field, &value);
	DEBUG_LOG("<ERROR> "<<(char*)(value->pointer));
}

Mono::MonoObject* Mono::create_csharp_string(char* ptr)
{
	auto* image = get_mscorlib();
	auto* pClass = Mono::mono_class_from_name(image, "System.Runtime.InteropServices", "Marshal");
	auto* method = mono_class_get_method_from_name(pClass, "PtrToStringUTF8", -1);

	void* params[2];
	params[0] = &ptr;
	params[1] = new int(strlen(ptr));

	MonoObject* excepion = nullptr;

	auto* nigger = (MonoObject*)Mono::mono_runtime_invoke(method, NULL, params, &excepion);

	if (excepion != nullptr)
	{
		DEBUG_LOG("NIGGER ERROR");
	}

	return nigger;
}

Mono::MonoClass* Mono::get_object_class()
{
	return mono_class_from_name(get_mscorlib(), "System", "Object");
}

HMODULE Mono::getModule()
{
	static HMODULE hModule = hModule = GetModuleHandle(L"mono-2.0-bdwgc.dll");
	
	return hModule;
}

Mono::MonoImage* Mono::get_script_image()
{
	static MonoImage* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
	
	return image;
}

Mono::MonoImage* Mono::get_mscorlib()
{
	static MonoImage* image = image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\mscorlib.dll");

	return image;
}

Mono::MonoImage* Mono::get_UE_CoreModule()
{
	static MonoImage* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\UnityEngine.CoreModule.dll");

	return image;
}


void Mono::implement()
{
	auto* module = getModule();
	Mono::mono_array_new = (MonoArray * (WINAPI*)(MonoDomain*, MonoClass*, uintptr_t))GetProcAddress(module, "mono_array_new");
	Mono::mono_object_new = (MonoObject * (WINAPI*)(MonoDomain*, MonoClass*))GetProcAddress(module, "mono_object_new");
	Mono::mono_image_loaded = (MonoImage * (WINAPI*)(const char*))GetProcAddress(module, "mono_image_loaded");
	Mono::mono_get_root_domain = (MonoDomain * (WINAPI*)())GetProcAddress(module, "mono_get_root_domain");
	Mono::mono_method_desc_new = (MonoMethodDesc * (WINAPI*)(const char*, bool))GetProcAddress(module, "mono_method_desc_new");
	Mono::mono_method_desc_free = (void(WINAPI*)(MonoMethodDesc*))GetProcAddress(module, "mono_method_desc_free");
	Mono::mono_method_desc_search_in_class = (MonoMethod * (WINAPI*)(MonoMethodDesc*, MonoClass*))GetProcAddress(module, "mono_method_desc_search_in_class");
	Mono::mono_object_get_virtual_method = (MonoMethod * (WINAPI *)(MonoObject * , MonoMethod * ))GetProcAddress(module, "mono_object_get_virtual_method");
	Mono::mono_class_get_method_from_name = (MonoMethod * (WINAPI*)(MonoClass * , const char* , int ))GetProcAddress(module, "mono_class_get_method_from_name");
	Mono::mono_property_get_get_method = (MonoMethod * (WINAPI*)(MonoProperty *))GetProcAddress(module, "mono_property_get_get_method");
	Mono::mono_property_get_set_method = (MonoMethod * (WINAPI*)(MonoProperty *))GetProcAddress(module, "mono_property_get_set_method");
	Mono::mono_class_get_name = (const char* (WINAPI*)(MonoClass *))GetProcAddress(module, "mono_class_get_name");
	Mono::mono_method_get_token = (UINT(WINAPI*)(MonoMethod * ))GetProcAddress(module, "mono_method_get_token");
	Mono::mono_method_get_name = (const char* (WINAPI*)(MonoMethod *))GetProcAddress(module, "mono_method_get_name");
	Mono::mono_class_vtable = (MonoVTable * (WINAPI*)(MonoDomain *, MonoClass *))GetProcAddress(module, "mono_class_vtable");
	Mono::mono_field_static_get_value = (void(WINAPI*)(MonoVTable *, MonoClassField *, void*))GetProcAddress(module, "mono_field_static_get_value");  
	Mono::mono_class_from_name = (MonoClass * (WINAPI*)(MonoImage *, const char*, const char*))GetProcAddress(module, "mono_class_from_name");
	Mono::mono_object_get_class = (MonoClass * (WINAPI*)(MonoObject *))GetProcAddress(module, "mono_object_get_class");
	Mono::mono_class_get_parent = (MonoClass * (WINAPI*)(MonoClass *))GetProcAddress(module, "mono_class_get_parent");
	Mono::mono_class_get_field = (MonoClassField * (WINAPI*)(MonoClass *, UINT))GetProcAddress(module, "mono_class_get_field");
	Mono::mono_field_from_token = (MonoClassField * (WINAPI*)(UINT))GetProcAddress(module, "mono_field_from_token");
	Mono::mono_class_get_field_from_name = (MonoClassField * (WINAPI*)(MonoClass *, const char*))GetProcAddress(module, "mono_class_get_field_from_name");
	Mono::mono_field_get_name = (const char* (WINAPI*)(MonoClassField *))GetProcAddress(module, "mono_field_get_name");
	Mono::mono_field_get_value = (void (WINAPI*)(MonoObject *, MonoClassField *, void*))GetProcAddress(module, "mono_field_get_value");
	Mono::mono_field_get_offset = (UINT(WINAPI*)(MonoClassField * ))GetProcAddress(module, "mono_field_get_offset");
	Mono::mono_class_get_field_token = (UINT(WINAPI*)(MonoClassField *))GetProcAddress(module, "mono_class_get_field_token");
	Mono::mono_class_get_property_from_name = (MonoProperty * (WINAPI*)(MonoClass *, const char*))GetProcAddress(module, "mono_class_get_property_from_name");
	Mono::mono_class_get_fields = (MonoClassField * (WINAPI*)(MonoClass *, void*))GetProcAddress(module, "mono_class_get_fields");
	Mono::mono_class_get_methods = (MonoMethod * (WINAPI*)(MonoClass *, void*))GetProcAddress(module, "mono_class_get_methods");
	Mono::mono_thread_attach = (void(WINAPI*)(MonoDomain *))GetProcAddress(module, "mono_thread_attach");
	Mono::mono_runtime_invoke = (void* (WINAPI*)(MonoMethod * , void* , void** , MonoObject **))GetProcAddress(module, "mono_runtime_invoke");
}
