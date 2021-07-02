#pragma once
#include "../MonoDefs.h"
namespace Mono
{
	typedef struct _MonoJitInfo MonoJitInfo;
	typedef struct _MonoMethodHeader MonoMethodHeader;
	typedef struct _MonoAssembly MonoAssembly;
	
	struct vTable
	{
	public:
		MonoArray* (WINAPI* mono_array_new)(MonoDomain* domain, MonoClass* eclass, uintptr_t n);
		MonoObject* (WINAPI* mono_object_new)(MonoDomain* domain, MonoClass* klass);
		UINT(WINAPI* mono_object_get_size)(MonoObject* o);
		MonoImage* (WINAPI* mono_image_loaded)(const char* name);
		const char* (WINAPI* mono_image_get_filename)(MonoImage* image);
		const char* (WINAPI* mono_image_get_name)(MonoImage* image);
		
		MonoDomain* (WINAPI* mono_get_root_domain)();
		MonoMethodDesc* (WINAPI* mono_method_desc_new)(const char* name, bool include_namespace);
		void	           (WINAPI* mono_method_desc_free)(MonoMethodDesc* pDesc);

		MonoMethod* (WINAPI* mono_method_desc_search_in_class)(MonoMethodDesc* desc, MonoClass* class_name);
		MonoMethod* (WINAPI* mono_object_get_virtual_method)(MonoObject* object, MonoMethod* method);
		MonoMethod* (WINAPI* mono_class_get_method_from_name)(MonoClass* klass, const char* name, int param_count);
		MonoMethod* (WINAPI* mono_property_get_get_method)(MonoProperty* prop);
		MonoMethod* (WINAPI* mono_property_get_set_method)(MonoProperty* prop);
		MonoObject* (WINAPI* mono_method_get_object)(MonoMethod* method);
		MonoClass* (WINAPI* mono_method_get_class)(MonoMethod* method);

		const char* (WINAPI* mono_class_get_name)(MonoClass* klass);
		UINT(WINAPI* mono_method_get_token)(MonoMethod* method);
		LPVOID(WINAPI* mono_method_get_unmanaged_thunk)(MonoMethod* method);
		const char* (WINAPI* mono_method_get_name)(MonoMethod* method);
		MonoVTable* (WINAPI* mono_class_vtable)(MonoDomain* domain, MonoClass* klass);
		void            (WINAPI* mono_field_static_get_value)(MonoVTable* vTable, MonoClassField* field, void* value);


		MonoClass* (WINAPI* mono_class_from_name)(MonoImage* image, const char* namespace_name, const char* name);
		MonoClass* (WINAPI* mono_object_get_class)(MonoObject* obj);
		const char* (WINAPI* mono_class_get_namespace)(MonoClass* obj);
		
		MonoClass* (WINAPI* mono_class_get_parent)(MonoClass* klass);
		UINT (WINAPI* mono_class_instance_size)(MonoClass* klass);

		MonoClassField* (WINAPI* mono_class_get_field)(MonoClass* klass, UINT field_token);
		MonoClassField* (WINAPI* mono_field_from_token)(UINT token);
		MonoClassField* (WINAPI* mono_class_get_field_from_name)(MonoClass* klass, const char* name);

		const char* (WINAPI* mono_field_get_name)(MonoClassField* pField);
		void            (WINAPI* mono_field_get_value)(MonoObject* object, MonoClassField* field, void* pValue);
		UINT(WINAPI* mono_field_get_offset)(MonoClassField* field);
		UINT(WINAPI* mono_class_get_field_token)(MonoClassField* field);
		MonoProperty* (WINAPI* mono_class_get_property_from_name)(MonoClass* klass, const char* name);

		
		MonoJitInfo* (WINAPI* mono_jit_info_table_find)(MonoDomain* domain,char* addr);
		LPVOID (WINAPI* mono_jit_info_get_code_start)(MonoJitInfo*);
		MonoMethod* (WINAPI* mono_jit_info_get_method)(MonoJitInfo*);


		MonoAssembly* (WINAPI* mono_domain_assembly_open)(MonoDomain*,const char*name);

				
		MonoMethodHeader* (WINAPI* mono_method_get_header)(MonoMethod*);
		LPVOID (WINAPI* mono_method_header_get_code)(MonoMethodHeader*, unsigned* code_size, unsigned* maxstack);
		LPVOID (WINAPI* mono_compile_method)(MonoMethod*);
		
		LPVOID (WINAPI* mono_disasm_code)(__int64, void*,void*,void*);

		//============================
		// ITERATORS
		// This routine is an iterator routine for retrieving the fields in a class.
		// (void* iter) pointer that points to zero
		// return MonoClassField* or NULL when no more fields available

		MonoClassField* (WINAPI* mono_class_get_fields)(MonoClass* klass, void* iter);
		MonoMethod* (WINAPI* mono_class_get_methods)(MonoClass* klass, void* iter);

		void            (WINAPI* mono_thread_attach)(MonoDomain* thread);
		void*			(WINAPI* mono_runtime_invoke)(MonoMethod* method, void* obj, void** params, MonoObject** exc);

	protected:
		static HMODULE getModule();
		void implement();
	};
}
