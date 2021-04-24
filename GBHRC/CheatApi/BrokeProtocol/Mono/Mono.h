#pragma once
#include "MonoDefs.h"
#include "../../../includes/win.h"
#include "dumper/MonoDumper.h"


namespace Mono
{
	
	void implement();

	static MonoArray*      (WINAPI* mono_array_new)(MonoDomain* domain, MonoClass* eclass, uintptr_t n);
	static MonoObject*     (WINAPI* mono_object_new)(MonoDomain* domain, MonoClass* klass);
	static MonoImage*      (WINAPI* mono_image_loaded)(const char* name);
	static MonoDomain*     (WINAPI* mono_get_root_domain)();
	static MonoMethodDesc* (WINAPI* mono_method_desc_new)(const char* name, bool include_namespace);
	static void	           (WINAPI* mono_method_desc_free)(MonoMethodDesc* pDesc);
	
	static MonoMethod*     (WINAPI* mono_method_desc_search_in_class)(MonoMethodDesc* desc, MonoClass* class_name);
	static MonoMethod*     (WINAPI* mono_object_get_virtual_method)(MonoObject* object, MonoMethod* method);
	static MonoMethod*     (WINAPI* mono_class_get_method_from_name)(MonoClass* klass, const char* name, int param_count);
	static MonoMethod*     (WINAPI* mono_property_get_get_method)(MonoProperty* prop);
	static MonoMethod*     (WINAPI* mono_property_get_set_method)(MonoProperty* prop);
	MonoMethod*            mono_get_method_from_image(MonoImage* image, const char* desc, bool include_namespace = true, int param_count = -1);

						   
	static const char*     (WINAPI* mono_class_get_name)(MonoClass* klass);
	static UINT            (WINAPI* mono_method_get_token)(MonoMethod* method);
	static LPVOID          (WINAPI* mono_method_get_unmanaged_thunk)(MonoMethod* method);
	static const char*     (WINAPI* mono_method_get_name)(MonoMethod* method);
	static MonoVTable*     (WINAPI* mono_class_vtable)(MonoDomain* domain, MonoClass* klass);
	static void            (WINAPI* mono_field_static_get_value)(MonoVTable* vTable, MonoClassField* field, void* value);
						   
	void                   WINAPI mono_get_static_field_value(MonoClass* klass, UINT token,void* value);
						   
	static MonoClass*      (WINAPI* mono_class_from_name)(MonoImage* image, const char* namespace_name, const char* name);
	static MonoClass*      (WINAPI* mono_object_get_class)(MonoObject* obj);
	static MonoClass*      (WINAPI* mono_class_get_parent)(MonoClass* klass);
	
	static MonoClassField* (WINAPI* mono_class_get_field)(MonoClass* klass, UINT field_token);
	static MonoClassField* (WINAPI* mono_field_from_token)(UINT token);
	static MonoClassField* (WINAPI* mono_class_get_field_from_name)(MonoClass* klass, const char* name);
	
	static const char*     (WINAPI* mono_field_get_name)(MonoClassField* pField);
	static void            (WINAPI* mono_field_get_value)(MonoObject* object, MonoClassField* field, void* pValue);
	void                   WINAPI mono_field_from_name_get_value(MonoObject* object, const char* name,void*pValue);
	static UINT            (WINAPI* mono_field_get_offset)(MonoClassField* field);
	static UINT            (WINAPI* mono_class_get_field_token)(MonoClassField* field);
	static MonoProperty*   (WINAPI* mono_class_get_property_from_name)(MonoClass* klass, const char* name);

	//============================
	// ITERATORS
	// This routine is an iterator routine for retrieving the fields in a class.
	// (void* iter) pointer that points to zero
	// return MonoClassField* or NULL when no more fields available

	static MonoClassField* (WINAPI* mono_class_get_fields)(MonoClass* klass, void* iter);
	static MonoMethod*     (WINAPI* mono_class_get_methods)(MonoClass* klass, void* iter);
	
	static void            (WINAPI* mono_thread_attach)(MonoDomain* thread);
	static void*           (WINAPI* mono_runtime_invoke)(MonoMethod* method, void* obj, void** params, MonoObject** exc);
	void  WINAPI           mono_print_system_exception(void* exception);
	
	MonoObject*            create_csharp_string(char* ptr);
	MonoClass*             get_object_class();
	
	MonoImage*             get_script_image();
	MonoImage*             get_mscorlib();
	MonoImage*             get_UE_CoreModule();

	HMODULE                getModule();

}
