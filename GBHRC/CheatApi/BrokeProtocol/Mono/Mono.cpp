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

char* Mono::mono_get_root_domain()
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_get_root_domain");

	return ((char * (__stdcall*)())proc)();
}

void Mono::mono_thread_attach(char* thread)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_thread_attach");

	return ((void(__stdcall*)(char*))proc)(thread);
}

void Mono::mono_runtime_invoke(MonoMethod* method, void* obj, void** params, void** exc)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_runtime_invoke");

	((MonoMethod * (__stdcall*)(MonoMethod * method, void* obj, void** params, void** exc))proc)(method,obj,params,exc);
}

const char* Mono::mono_class_get_name(MonoClass* klass)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_class_get_name");

	return ((const char * (__stdcall*)(MonoClass *))proc)(klass);
}

void Mono::mono_print_unhandled_exception(void* exception)
{
	static LPVOID proc;
	if (proc == nullptr)
		proc = GetProcAddress(getModule(), "mono_print_unhandled_exception");

	((const char* (__stdcall*)(void*))proc)(exception);
}

HMODULE Mono::getModule()
{
	static HMODULE hModule;
	if(hModule==0)
		hModule = GetModuleHandle(L"mono-2.0-bdwgc.dll");
	
	return hModule;
}
