#include "Mono.h"

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

UINT Mono::mono_field_get_offset(MonoClassField* field)
{
	STATIC_PROCEDURE("mono_field_get_offset")

	return ((UINT(__stdcall*)(MonoClassField*))proc)(field);
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

Mono::MonoClass* Mono::mono_class_from_name(MonoImage* image, const char* namespace_name, const char* name)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_class_from_name");

	return ((MonoClass*(__stdcall*)(MonoImage*,const char*,const char*))proc)(image,namespace_name,name);
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

void* Mono::mono_runtime_invoke(MonoMethod* method, void* obj, void** params, void** exc)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_runtime_invoke");

	return ((void*(__stdcall*)(MonoMethod * method, void* obj, void** params, void** exc))proc)(method,obj,params,exc);
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

Mono::MonoClassField* Mono::mono_class_get_fields(MonoClass* klass, void* iter)
{
	STATIC_PROCEDURE("mono_class_get_fields")
	return ((MonoClassField * (__stdcall*)(MonoDomain*, void*))proc)(klass, iter);
}

void* Mono::create_csharp_string(char* ptr)
{
	//CtorCharPtr
	auto* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\mscorlib.dll");

	auto* pClass = Mono::mono_class_from_name(image, "System.Runtime.InteropServices", "Marshal");

	DEBUG_LOG("CLASS: " << pClass);
	// char* ptr,int bytelenght
	auto* method = mono_class_get_method_from_name(pClass, "PtrToStringUTF8", -1);
	DEBUG_LOG("METHOD: " << method);

	void* params[2];
	params[0] = &ptr;
	params[1] = new int(strlen(ptr));

	void* excepion = nullptr;

	void* nigger = Mono::mono_runtime_invoke(method, NULL, params, &excepion);

	if (excepion != nullptr)
	{
		DEBUG_LOG("NIGGER ERROR");
		Mono::mono_print_unhandled_exception(excepion);
	}

	DEBUG_LOG("STRING:"<<nigger);

	return nigger;
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