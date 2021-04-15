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
	typedef void MonoType;

	typedef struct {
		MonoVTable* vtable;
		void* synchronisation;
	} MonoObject;

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

	typedef struct {
		UINT length;
		UINT lower_bound;
	} MonoArrayBounds;

	typedef struct {
		MonoObject obj;
		/* bounds is NULL for szarrays */
		MonoArrayBounds* bounds;
		/* total number of elements of the array */
		UINT max_length;
		/* we use double to ensure proper alignment on platforms that need it */
		__int64 vector[0];
	} MonoArray;

	MonoArray*  WINAPI mono_array_new(MonoDomain* domain, MonoClass* eclass, uintptr_t n);

	MonoObject* WINAPI mono_object_new(MonoDomain* domain, MonoClass* klass);
	
	MonoImage*  WINAPI mono_image_loaded(const char* name);
	MonoDomain* WINAPI mono_get_root_domain();
	
	MonoMethodDesc* WINAPI mono_method_desc_new(const char* name, bool include_namespace);
	void        WINAPI mono_method_desc_free(MonoMethodDesc* pDesc);

	MonoMethod* WINAPI mono_method_desc_search_in_class(MonoMethodDesc* desc, MonoClass* class_name);
	MonoMethod* WINAPI mono_object_get_virtual_method(MonoObject* object, MonoMethod* method);
	MonoMethod* WINAPI mono_class_get_method_from_name(MonoClass* klass, const char* name, int param_count);
	const char* WINAPI mono_class_get_name(MonoClass* klass);
	
	LPVOID      WINAPI mono_method_get_unmanaged_thunk(MonoMethod* method);

	MonoVTable* WINAPI mono_class_vtable(MonoDomain* domain, MonoClass* klass);
	void        WINAPI mono_field_static_get_value(MonoVTable* vTable, MonoClassField* field, void* value);
	MonoClass*  WINAPI mono_class_from_name(MonoImage* image, const char* namespace_name, const char* name);
	MonoClass*  WINAPI mono_object_get_class(MonoObject* obj);
	
	MonoClassField* mono_class_get_field(MonoClass* klass, UINT field_token);
	MonoClassField* mono_field_from_token(UINT token);
	MonoClassField* mono_class_get_field_from_name(MonoClass* klass, const char* name);
	const char*     mono_field_get_name(MonoClassField* pField);
	void            mono_field_get_value(MonoObject* object, MonoClassField* field, void* pValue);
	UINT            mono_field_get_offset(MonoClassField* field);

	MonoProperty* mono_class_get_property_from_name(MonoClass* klass, const char* name);
	MonoMethod* mono_property_get_get_method(MonoProperty* prop);
	
	/// <summary>
	/// This routine is an iterator routine for retrieving the fields in a class.
	/// </summary>
	/// <param name="klass"></param>
	/// <param name="iter">pointer that points to zero</param>
	/// <returns>MonoClassField* or NULL when no more fields available</returns>
	MonoClassField* mono_class_get_fields(MonoClass* klass, void* iter);
	MonoMethod*     mono_class_get_methods(MonoClass* klass, void* iter);

	char* mono_type_get_name(MonoType* type);
	
	void  WINAPI mono_thread_attach(MonoDomain* thread);
	void* WINAPI mono_runtime_invoke(MonoMethod* method, void* obj, void** params, MonoObject** exc);
	
	void  WINAPI mono_error_raise_exception(void** error);
	void  WINAPI mono_print_unhandled_exception(void* exception);
	
	MonoObject* create_csharp_string(char* ptr);
	MonoClass* get_object_class();

	void mono_dump_class(MonoClass* klass);
	
	HMODULE getModule();
	MonoImage* get_script_image();
	MonoImage* get_mscorlib();
}
