#pragma once
#include "../../../includes/win.h"

namespace Mono
{
	typedef struct MonoVTable MonoVTable;

	typedef struct _MonoClassField MonoClassField;
	typedef struct _MonoProperty MonoProperty;
	typedef struct _MonoEvent MonoEvent;
	typedef struct _MonoMethod MonoMethod;
	typedef struct _MonoImage MonoImage;
	typedef void MonoDomain;
	typedef void MonoDomain;
	typedef void MonoObject;

	typedef struct
	{
		const char* namespace_name;
		const char* class_name;
		const char* method_name;
		const char* arguments;
		const char* unknown_data;
	} MonoMethodDesc;

	typedef struct {
		MonoObject* object;
		int length;
		unsigned char chars[0];
	} MonoString;

	typedef struct _MonoClass MonoClass;

	typedef enum {
		MONO_TYPE_NAME_FORMAT_IL,
		MONO_TYPE_NAME_FORMAT_REFLECTION,
		MONO_TYPE_NAME_FORMAT_FULL_NAME,
		MONO_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED
	} MonoTypeNameFormat;
	
	MonoMethodDesc* WINAPI mono_method_desc_new(const char* name, bool include_namespace);
	void mono_method_desc_free(MonoMethodDesc* pDesc);
	LPVOID WINAPI mono_method_get_unmanaged_thunk(MonoMethod* method);

	
	MonoClassField* WINAPI mono_class_get_field(MonoClass* klass, UINT field_token);
	MonoClassField* mono_field_from_token(UINT token);
	const char* mono_field_get_name(MonoClassField* pField);
	void mono_field_get_value(MonoObject* object, MonoClassField* field, void* pValue);
	UINT mono_field_get_offset(MonoClassField* field);

	MonoVTable* mono_class_vtable(MonoDomain* domain, MonoClass* klass);
	void mono_field_static_get_value(MonoVTable* vTable, MonoClassField* field, void* value);
	
	
	MonoClass* WINAPI mono_class_from_name(MonoImage* image, const char* namespace_name, const char* name);
	MonoImage* WINAPI mono_image_loaded(const char* name);
	MonoMethod* WINAPI mono_class_get_method_from_name(MonoClass* klass, const char* name, int param_count);
	MonoClass* mono_object_get_class(MonoObject* obj);
	MonoMethod* WINAPI mono_object_get_virtual_method(MonoObject* object, MonoMethod* method);
	MonoMethod* WINAPI mono_method_desc_search_in_class(MonoMethodDesc* desc, MonoClass* class_name);
	
	void mono_thread_attach(MonoDomain* thread);
	void* WINAPI mono_runtime_invoke(MonoMethod* method, void* obj, void** params, void** exc);
	const char* WINAPI mono_class_get_name(MonoClass* klass);

	void mono_error_raise_exception(void** error);
	void mono_print_unhandled_exception(void* exception);

	MonoDomain* mono_get_root_domain();

	/// <summary>
	/// This routine is an iterator routine for retrieving the fields in a class.
	/// </summary>
	/// <param name="klass"></param>
	/// <param name="iter">pointer that points to zero</param>
	/// <returns>MonoClassField* or NULL when no more fields available</returns>
	MonoClassField* mono_class_get_fields(MonoClass* klass, void* iter);
	
	MonoString* mono_string_new(MonoDomain* domain, const char* text);
	void* create_csharp_string(char* ptr);
	
	HMODULE getModule();

	void mono_dump_class(MonoClass* klass);
}
