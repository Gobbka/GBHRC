#include "Mono.h"


#include "../BPStructs.h"
#include "../../../includes/logger.h"

#define STATIC_PROCEDURE(proc_name) static LPVOID proc; if(proc==nullptr) proc = GetProcAddress(getModule(),proc_name);

Mono::MonoMethodDesc* Mono::mono_method_desc_new(const char* name, bool include_namespace)
{
	typedef MonoMethodDesc* (__stdcall* tMonoMethodDescNew)(const char* name, bool include_namespace);
	static tMonoMethodDescNew proc;

	if (proc == nullptr)
		proc = (tMonoMethodDescNew)GetProcAddress(getModule(), "mono_method_desc_new");
	
	return proc(name, include_namespace);
}

void Mono::mono_method_desc_free(MonoMethodDesc* pDesc)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_method_desc_free");

	((const char* (__stdcall*)(MonoMethodDesc*))proc)(pDesc);
}

LPVOID Mono::mono_method_get_unmanaged_thunk(MonoMethod* method)
{
	typedef LPVOID(__stdcall* tMonoMethodDescNew)(MonoMethod*method);
	static tMonoMethodDescNew proc;

	if (proc == nullptr)
		proc = (tMonoMethodDescNew)GetProcAddress(getModule(), "mono_method_get_unmanaged_thunk");
	return proc(method);
}

const char* Mono::mono_method_get_name(MonoMethod* method)
{
	STATIC_PROCEDURE("mono_method_get_name")

	return ((const char * (__stdcall*)(MonoMethod*))proc)(method);
}

Mono::MonoClassField* Mono::mono_class_get_field(MonoClass* klass, UINT field_token)
{
	typedef MonoClassField* (__stdcall* tMonoClassGetField)(MonoClass* klass, UINT field_token);
	static tMonoClassGetField proc;

	if(proc==nullptr)
		proc = (tMonoClassGetField)GetProcAddress(getModule(), "mono_class_get_field");

	return proc(klass, field_token);
}

Mono::MonoClassField* Mono::mono_field_from_token(UINT token)
{
	STATIC_PROCEDURE("mono_field_get_name")

	return ((MonoClassField* (__stdcall*)(UINT))proc)(token);
}

Mono::MonoClassField* Mono::mono_class_get_field_from_name(MonoClass* klass, const char* name)
{
	STATIC_PROCEDURE("mono_field_get_name")

	return ((MonoClassField * (__stdcall*)(MonoClass*,const char*))proc)(klass,name);
}

const char* Mono::mono_field_get_name(MonoClassField* pField)
{
	STATIC_PROCEDURE("mono_field_get_name")
	
	return ((const char * (__stdcall*)(MonoClassField*))proc)(pField);
}

void Mono::mono_field_get_value(MonoObject* object, MonoClassField* field, void* pValue)
{
	STATIC_PROCEDURE("mono_field_get_value")
	
	((void(__stdcall*)(MonoObject*,MonoClassField*,void*))proc)(object,field,pValue);
}

void Mono::mono_field_from_name_get_value(MonoObject* object, const char* name, void* pValue)
{
	auto* pClass = mono_object_get_class(object);
	auto* field = mono_class_get_field_from_name(pClass, name);
	mono_field_get_value(object, field, pValue);
}

UINT Mono::mono_field_get_offset(MonoClassField* field)
{
	STATIC_PROCEDURE("mono_field_get_offset")

	return ((UINT(__stdcall*)(MonoClassField*))proc)(field);
}

UINT Mono::mono_class_get_field_token(MonoClassField* field)
{
	STATIC_PROCEDURE("mono_class_get_field_token")

	return ((UINT(__stdcall*)(MonoClassField*))proc)(field);
}

Mono::MonoProperty* Mono::mono_class_get_property_from_name(MonoClass* klass, const char* name)
{
	STATIC_PROCEDURE("mono_class_get_property_from_name")
	return ((MonoProperty * (__stdcall*)(MonoClass*, const char*))proc)(klass,name);
}

Mono::MonoMethod* Mono::mono_property_get_get_method(MonoProperty* prop)
{
	STATIC_PROCEDURE("mono_property_get_get_method")
	return ((MonoMethod * (__stdcall*)(MonoProperty*))proc)(prop);
}

Mono::MonoVTable* Mono::mono_class_vtable(MonoDomain* domain, MonoClass* klass)
{
	STATIC_PROCEDURE("mono_class_vtable")

	return ((MonoVTable*(__stdcall*)(MonoDomain*,MonoClass*))proc)(domain,klass);
}

void Mono::mono_field_static_get_value(MonoVTable* vTable, MonoClassField* field, void* value)
{
	STATIC_PROCEDURE("mono_field_static_get_value")

	return ((void(__stdcall*)(MonoVTable * vTable, MonoClassField * field, void* value))proc)(vTable,field,value);
}

void Mono::mono_get_static_field_value(MonoClass* klass, UINT token,void*value)
{
	auto* vTable = (Mono::MonoVTable*)Mono::mono_class_vtable(Mono::mono_get_root_domain(), klass);

	auto* static_class = Mono::mono_object_get_class((Mono::MonoObject*)vTable);
	auto* pPlayersCollectionField = Mono::mono_class_get_field(static_class, token);

	Mono::mono_field_static_get_value(vTable, pPlayersCollectionField, value);
}

Mono::MonoClass* Mono::mono_class_from_name(MonoImage* image, const char* namespace_name, const char* name)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_class_from_name");

	return ((MonoClass*(__stdcall*)(MonoImage*,const char*,const char*))proc)(image,namespace_name,name);
}

Mono::MonoArray* Mono::mono_array_new(MonoDomain* domain, MonoClass* eclass, uintptr_t n)
{
	STATIC_PROCEDURE("mono_array_new")
	return ((MonoArray* (__stdcall*)(MonoDomain*, MonoClass*,uintptr_t))proc)(domain, eclass,n);
}

Mono::MonoObject* Mono::mono_object_new(MonoDomain* domain, MonoClass* klass)
{
	STATIC_PROCEDURE("mono_object_new")
	return ((MonoObject * (__stdcall*)(MonoDomain*,MonoClass*))proc)(domain,klass);
}

Mono::MonoImage* Mono::mono_image_loaded(const char* name)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_image_loaded");

	return ((MonoImage*(__stdcall*)(const char* name))proc)(name);
}

Mono::MonoMethod* Mono::mono_class_get_method_from_name(MonoClass* klass, const char* name, int param_count)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_class_get_method_from_name");

	return ((MonoMethod * (__stdcall*)(MonoClass * klass, const char* name, int param_count))proc)(klass,name,param_count);
}

Mono::MonoClass* Mono::mono_object_get_class(MonoObject* obj)
{
	STATIC_PROCEDURE("mono_object_get_class")

	return ((MonoClass * (__stdcall*)(MonoObject*))proc)(obj);
}

Mono::MonoMethod* Mono::mono_object_get_virtual_method(MonoObject* object, MonoMethod* method)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_object_get_virtual_method");

	return ((MonoMethod * (__stdcall*)(MonoObject*, MonoMethod*))proc)(object,method);
}

Mono::MonoMethod* Mono::mono_method_desc_search_in_class(MonoMethodDesc* desc, MonoClass* class_name)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_method_desc_search_in_class");

	return ((MonoMethod * (__stdcall*)(MonoMethodDesc*, MonoClass*))proc)(desc, class_name);
}

Mono::MonoDomain* Mono::mono_get_root_domain()
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_get_root_domain");

	return ((MonoDomain * (__stdcall*)())proc)();
}

void Mono::mono_thread_attach(MonoDomain* thread)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_thread_attach");

	return ((void(__stdcall*)(MonoDomain*))proc)(thread);
}

void* Mono::mono_runtime_invoke(MonoMethod* method, void* obj, void** params, MonoObject** exc)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_runtime_invoke");

	return ((void*(__stdcall*)(MonoMethod * method, void* obj, void** params, MonoObject** exc))proc)(method,obj,params,exc);
}

const char* Mono::mono_class_get_name(MonoClass* klass)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_class_get_name");

	return ((const char * (__stdcall*)(MonoClass *))proc)(klass);
}

void Mono::mono_error_raise_exception(void** error)
{
	STATIC_PROCEDURE("mono_error_raise_exception")

	((void(__stdcall*)(void**))proc)(error);
}

void Mono::mono_print_unhandled_exception(void* exception)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_print_unhandled_exception");

	((const char* (__stdcall*)(void*))proc)(exception);
}

void Mono::mono_print_system_exception(void* exception)
{
	auto* klass = Mono::mono_class_from_name(get_mscorlib(), "System", "Exception");
	auto* field = Mono::mono_class_get_field_from_name(klass, "_message");
	BrokeProtocol::Structs::String* value;
	mono_field_get_value((MonoObject*)exception, field, &value);
	DEBUG_LOG("<ERROR> "<<(char*)(value->pointer));
}

Mono::MonoClassField* Mono::mono_class_get_fields(MonoClass* klass, void* iter)
{
	STATIC_PROCEDURE("mono_class_get_fields")
	return ((MonoClassField * (__stdcall*)(MonoDomain*, void*))proc)(klass, iter);
}

Mono::MonoMethod* Mono::mono_class_get_methods(MonoClass* klass, void* iter)
{
	STATIC_PROCEDURE("mono_class_get_methods")
	return ((MonoMethod * (__stdcall*)(MonoDomain*, void*))proc)(klass, iter);
}

char* Mono::mono_type_get_name(MonoType* type)
{
	STATIC_PROCEDURE("mono_type_get_name")
	return ((char * (__stdcall*)(MonoType*))proc)(type);
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
		Mono::mono_print_unhandled_exception(excepion);
	}

	return nigger;
}

Mono::MonoClass* Mono::get_object_class()
{
	return mono_class_from_name(get_mscorlib(), "System", "Object");
}

HMODULE Mono::getModule()
{
	static HMODULE hModule;
	if(hModule==0)
		hModule = GetModuleHandle(L"mono-2.0-bdwgc.dll");
	
	return hModule;
}

Mono::MonoImage* Mono::get_script_image()
{
	static MonoImage* image;
	if(image == nullptr)
		image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
	
	return image;
}

Mono::MonoImage* Mono::get_mscorlib()
{
	static MonoImage* image;
	if (image == nullptr)
		image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\mscorlib.dll");

	return image;
}

void Mono::mono_dump_class(MonoClass* klass)
{
	void* pointer = NULL;
	Mono::MonoClassField* field = NULL;

	DEBUG_LOG("====== " << Mono::mono_class_get_name(klass) << " ======");
	while ((field = Mono::mono_class_get_fields(klass, &pointer)))
	{
		DEBUG_LOG("0x"<<std::hex<<mono_field_get_offset(field)<<" : "<<mono_field_get_name(field));
	}
	DEBUG_LOG("=========================");
}
